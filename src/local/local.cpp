#include <stdinclude.hpp>

using namespace std;

namespace local
{
	namespace
	{
		unordered_map<size_t, wstring> text_db;
		std::vector<size_t> str_list;

		wstring u8_wide(u8string str)
		{
			wstring result;
			result.resize(str.length());

			MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<char*>(str.data()),
								str.size(), result.data(), result.length());

			return result;
		}
	}

	wstring u8_wide(string str)
	{
		u8string temp;
		temp.resize(str.size());
		str.copy(reinterpret_cast<char*>(temp.data()), str.size());
		return u8_wide(temp);
	}

	string wide_u8(wstring str)
	{
		string result;
		result.resize(str.length() * 4);

		int len = WideCharToMultiByte(CP_UTF8, 0, str.data(), str.length(), result.data(), result.size(), nullptr, nullptr);

		result.resize(len);

		return result;
	}

	void load_textdb(const vector<string> *dicts)
	{
		for (auto dict : *dicts)
		{
			if (filesystem::exists(dict))
			{
				std::ifstream dict_stream {dict};

				if (!dict_stream.is_open())
					continue;

				printf("Reading %s...\n", dict.data());

				rapidjson::IStreamWrapper wrapper {dict_stream};
				rapidjson::Document document;

				document.ParseStream(wrapper);

				for (auto iter = document.MemberBegin(); 
					 iter != document.MemberEnd(); ++iter)
				{
					auto key = std::stoull(iter->name.GetString());
					auto value = u8_wide(iter->value.GetString());

					text_db.emplace(key, value);
				}

				dict_stream.close();
			}
		}

		printf("loaded %llu localized entries.\n", text_db.size());
	}

	bool localify_text(size_t hash, wstring** result)
	{
		if (text_db.contains(hash))
		{
			*result = &text_db[hash];
			return true;
		}

		return false;
	}

	Il2CppString* get_localized_string(size_t hash_or_id)
	{
		wstring* result;

		if (local::localify_text(hash_or_id, &result))
		{
			return il2cpp_string_new_utf16(result->data(), result->length());
		}

		return nullptr;
	}

	Il2CppString* get_localized_string(Il2CppString* str)
	{
		wstring* result;

		auto hash = std::hash<wstring> {}(str->start_char);

		if (local::localify_text(hash, &result))
		{
			return il2cpp_string_new_utf16(result->data(), result->length());
		}

		if (g_enable_logger && !std::any_of(str_list.begin(), str_list.end(), [hash](size_t hash1) { return hash1 == hash; }))
		{
			str_list.push_back(hash);

			logger::write_entry(hash, str->start_char);
		}

		return str;
	}
}
