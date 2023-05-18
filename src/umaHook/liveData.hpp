#pragma once

#include "stdinclude.hpp"

enum class LiveDelegateType {
	UNSET,
	OnUpdatePostEffect_DOF,
	OnUpdateVolumeLight
};

namespace LiveData {
	namespace {
		template <typename T>
		void changeValueByType(T* p1, T* p2, bool condition) {
			if (condition) {
				*p1 = *p2;
			}
			else {
				*p2 = *p1;
			}
		}
	}

	std::unordered_map<LiveDelegateType, void*> LiveUpdateInfoDelegates{};
	std::unordered_map<LiveDelegateType, std::pair<void*, std::pair<const char*, const char*>>> LiveUpdateInfoDelegatesInvoke{};

	void* getDelegate(LiveDelegateType type) {
		if (const auto iter = LiveUpdateInfoDelegates.find(type); iter != LiveUpdateInfoDelegates.end()) {
			return iter->second;
		}
		return NULL;
	}

	bool checkDelegate(LiveDelegateType type, void* ptr) {
		return getDelegate(type) == ptr;
	}

	template <class T>
	class ILiveUpdateInfo {
	public:
		virtual void updateData() = 0;

		LiveDelegateType myType = LiveDelegateType::UNSET;

		void generateUpdateInfo(const char* namespaze, const char* klassName) {
			const auto klass = il2cpp_symbols::get_class("umamusume.dll", namespaze, klassName);
			updateInfo = reinterpret_cast<T*>(il2cpp_object_new(klass));
		}

		void generateUpdateInfo() {
			if (const auto iter = LiveUpdateInfoDelegatesInvoke.find(myType); iter != LiveUpdateInfoDelegatesInvoke.end()) {
				generateUpdateInfo(iter->second.second.first, iter->second.second.second);
			}
		}

		void updateGame(bool reGenerateUpdateInfo = false) {
			auto gameDelegate = getDelegate(myType);
			if (gameDelegate != NULL) {
				if (const auto iter = LiveUpdateInfoDelegatesInvoke.find(myType); iter != LiveUpdateInfoDelegatesInvoke.end()) {
					auto invokeMtd = iter->second.first;
					if (reGenerateUpdateInfo || (!updateInfo)) {
						generateUpdateInfo(iter->second.second.first, iter->second.second.second);
					}

					if (invokeMtd) {
						updateData();
						reinterpret_cast<void (*)(void*, void*)>(invokeMtd)(gameDelegate, updateInfo);
					}
				}
				else {
					printf("UpdateInfoDelegates_Invoke: %d not found!\n", myType);
				}
			}
		}

	protected:
		T* localData;
		T* updateInfo;
		bool condition;
	};

	void* PostEffectUpdateInfo_DOF_klass;
	FieldInfo* PostEffectUpdateInfo_DOF_forcalPosition;
	void* PostFilmUpdateInfo_klass;
	FieldInfo* PostFilmUpdateInfo_filmOffsetParam;
	FieldInfo* PostFilmUpdateInfo_filmOptionParam;
	FieldInfo* PostFilmUpdateInfo_color0;
	FieldInfo* PostFilmUpdateInfo_color1;
	FieldInfo* PostFilmUpdateInfo_color2;
	FieldInfo* PostFilmUpdateInfo_color3;
	FieldInfo* PostFilmUpdateInfo_FilmScale;

	bool isffinit = false;
	void init_LiveFieldData() {
		if (isffinit) return;
		PostEffectUpdateInfo_DOF_klass = il2cpp_symbols::get_class("umamusume.dll", "Gallop.Live.Cutt", "PostEffectUpdateInfo_DOF");
		PostEffectUpdateInfo_DOF_forcalPosition = il2cpp_class_get_field_from_name(PostEffectUpdateInfo_DOF_klass, "forcalPosition");
		
		PostFilmUpdateInfo_klass = il2cpp_symbols::get_class("umamusume.dll", "Gallop.Live.Cutt", "PostFilmUpdateInfo");
		PostFilmUpdateInfo_filmOffsetParam = il2cpp_class_get_field_from_name(PostFilmUpdateInfo_klass, "filmOffsetParam");
		PostFilmUpdateInfo_filmOptionParam = il2cpp_class_get_field_from_name(PostFilmUpdateInfo_klass, "filmOptionParam");
		PostFilmUpdateInfo_color0 = il2cpp_class_get_field_from_name(PostFilmUpdateInfo_klass, "color0");
		PostFilmUpdateInfo_color1 = il2cpp_class_get_field_from_name(PostFilmUpdateInfo_klass, "color1");
		PostFilmUpdateInfo_color2 = il2cpp_class_get_field_from_name(PostFilmUpdateInfo_klass, "color2");
		PostFilmUpdateInfo_color3 = il2cpp_class_get_field_from_name(PostFilmUpdateInfo_klass, "color3");
		PostFilmUpdateInfo_FilmScale = il2cpp_class_get_field_from_name(PostFilmUpdateInfo_klass, "FilmScale");
		isffinit = true;
	}

	class PostEffectUpdateInfo_DOF : public ILiveUpdateInfo<UmaGUiShowData::PostEffectUpdateInfo_DOF> {
	public:
		PostEffectUpdateInfo_DOF(UmaGUiShowData::PostEffectUpdateInfo_DOF* updateInfo, bool condition) {
			localData = &UmaGUiShowData::postEffectUpdateInfo_DOF;
			this->updateInfo = updateInfo;
			this->condition = condition;
			myType = LiveDelegateType::OnUpdatePostEffect_DOF;
		}

		void updateData() {
			init_LiveFieldData();
			if (!updateInfo) generateUpdateInfo();

			changeValueByType(&localData->IsEnableDOF, &updateInfo->IsEnableDOF, condition);
			changeValueByType(&localData->forcalSize, &updateInfo->forcalSize, condition);
			changeValueByType(&localData->blurSpread, &updateInfo->blurSpread, condition);
			changeValueByType(&localData->dofQuality, &updateInfo->dofQuality, condition);
			changeValueByType(&localData->dofBlurType, &updateInfo->dofBlurType, condition);
			changeValueByType(&localData->dofForegroundSize, &updateInfo->dofForegroundSize, condition);
			changeValueByType(&localData->dofFocalPoint, &updateInfo->dofFocalPoint, condition);
			changeValueByType(&localData->dofSoomthness, &updateInfo->dofSoomthness, condition);
			changeValueByType(&localData->isUseFocalPoint, &updateInfo->isUseFocalPoint, condition);
			changeValueByType(&localData->BallBlurCurveFactor, &updateInfo->BallBlurCurveFactor, condition);
			changeValueByType(&localData->BallBlurBrightnessThreshhold, &updateInfo->BallBlurBrightnessThreshhold, condition);
			changeValueByType(&localData->BallBlurBrightnessIntensity, &updateInfo->BallBlurBrightnessIntensity, condition);
			changeValueByType(&localData->BallBlurSpread, &updateInfo->BallBlurSpread, condition);
			changeValueByType(&localData->IsPointBallBlur, &updateInfo->IsPointBallBlur, condition);

			auto forcalPosition = reinterpret_cast<Vector3_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostEffectUpdateInfo_DOF_forcalPosition->offset
				);
			changeValueByType(&UmaGUiShowData::liveDOFForcalPosition.x, &forcalPosition->x, condition);
			changeValueByType(&UmaGUiShowData::liveDOFForcalPosition.y, &forcalPosition->y, condition);
			changeValueByType(&UmaGUiShowData::liveDOFForcalPosition.z, &forcalPosition->z, condition);

		}
	};

	class PostFilmUpdateInfo : public ILiveUpdateInfo<UmaGUiShowData::PostFilmUpdateInfo> {
	protected:
		Vector2_t* _filmOffsetParam;
		Vector2_t* _FilmScale;
		Vector4_t* _filmOptionParam;
		Color_t* _filmcolor0;
		Color_t* _filmcolor1;
		Color_t* _filmcolor2;
		Color_t* _filmcolor3;

	public:
		PostFilmUpdateInfo(UmaGUiShowData::PostFilmUpdateInfo* updateInfo, bool condition, int index) {
			localData = &UmaGUiShowData::postFilmUpdateInfo[index];
			this->updateInfo = updateInfo;
			this->condition = condition;
			myType = LiveDelegateType::OnUpdateVolumeLight;

			_filmOffsetParam = &UmaGUiShowData::filmOffsetParam[index];
			_FilmScale = &UmaGUiShowData::FilmScale[index];
			_filmOptionParam = &UmaGUiShowData::filmOptionParam[index];
			_filmcolor0 = &UmaGUiShowData::filmcolor0[index];
			_filmcolor1 = &UmaGUiShowData::filmcolor1[index];
			_filmcolor2 = &UmaGUiShowData::filmcolor2[index];
			_filmcolor3 = &UmaGUiShowData::filmcolor3[index];
		}

		void updateData() {
			init_LiveFieldData();
			changeValueByType(&localData->filmMode, &updateInfo->filmMode, condition);
			changeValueByType(&localData->colorType, &updateInfo->colorType, condition);
			changeValueByType(&localData->filmPower, &updateInfo->filmPower, condition);
			changeValueByType(&localData->depthPower, &updateInfo->depthPower, condition);
			changeValueByType(&localData->DepthClip, &updateInfo->DepthClip, condition);
			changeValueByType(&localData->layerMode, &updateInfo->layerMode, condition);
			changeValueByType(&localData->colorBlend, &updateInfo->colorBlend, condition);
			changeValueByType(&localData->inverseVignette, &updateInfo->inverseVignette, condition);
			changeValueByType(&localData->colorBlendFactor, &updateInfo->colorBlendFactor, condition);
			changeValueByType(&localData->movieResId, &updateInfo->movieResId, condition);
			changeValueByType(&localData->movieFrameOffset, &updateInfo->movieFrameOffset, condition);
			changeValueByType(&localData->movieTime, &updateInfo->movieTime, condition);
			changeValueByType(&localData->movieReverse, &updateInfo->movieReverse, condition);
			changeValueByType(&localData->RollAngle, &updateInfo->RollAngle, condition);
			
			auto filmOffsetParam = reinterpret_cast<Vector2_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostFilmUpdateInfo_filmOffsetParam->offset
				);	
			changeValueByType(&_filmOffsetParam->x, &filmOffsetParam->x, condition);
			changeValueByType(&_filmOffsetParam->y, &filmOffsetParam->y, condition);
			
			auto FilmScale = reinterpret_cast<Vector2_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostFilmUpdateInfo_FilmScale->offset
				);	
			changeValueByType(&_FilmScale->x, &FilmScale->x, condition);
			changeValueByType(&_FilmScale->y, &FilmScale->y, condition);

			auto filmOptionParam = reinterpret_cast<Vector4_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostFilmUpdateInfo_filmOptionParam->offset
				);	
			changeValueByType(&_filmOptionParam->x, &filmOptionParam->x, condition);
			changeValueByType(&_filmOptionParam->y, &filmOptionParam->y, condition);
			changeValueByType(&_filmOptionParam->z, &filmOptionParam->z, condition);
			changeValueByType(&_filmOptionParam->w, &filmOptionParam->w, condition);
			
			auto color0 = reinterpret_cast<Color_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostFilmUpdateInfo_color0->offset
				);
			changeValueByType(&_filmcolor0->r, &color0->r, condition);
			changeValueByType(&_filmcolor0->g, &color0->g, condition);
			changeValueByType(&_filmcolor0->b, &color0->b, condition);
			changeValueByType(&_filmcolor0->a, &color0->a, condition);
			auto color1 = reinterpret_cast<Color_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostFilmUpdateInfo_color1->offset
				);
			changeValueByType(&_filmcolor1->r, &color1->r, condition);
			changeValueByType(&_filmcolor1->g, &color1->g, condition);
			changeValueByType(&_filmcolor1->b, &color1->b, condition);
			changeValueByType(&_filmcolor1->a, &color1->a, condition);
			auto color2 = reinterpret_cast<Color_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostFilmUpdateInfo_color2->offset
				);
			changeValueByType(&_filmcolor2->r, &color2->r, condition);
			changeValueByType(&_filmcolor2->g, &color2->g, condition);
			changeValueByType(&_filmcolor2->b, &color2->b, condition);
			changeValueByType(&_filmcolor2->a, &color2->a, condition);
			auto color3 = reinterpret_cast<Color_t*>(
				static_cast<std::byte*>(reinterpret_cast<void*>(updateInfo)) + PostFilmUpdateInfo_color3->offset
				);
			changeValueByType(&_filmcolor3->r, &color3->r, condition);
			changeValueByType(&_filmcolor3->g, &color3->g, condition);
			changeValueByType(&_filmcolor3->b, &color3->b, condition);
			changeValueByType(&_filmcolor3->a, &color3->a, condition);
		}
	};

}
