#pragma once
#include "BaseCharacter.h"
#include "DirectXCommon.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


class Enemy : public BaseCharacter{
public:
	enum {
		kModelIndexBody,
		kModelIndexL_arm,
		kModelIndexR_arm,
	};

	float floatingPrameter = 0.0f;

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

	void UpdateGimmick();

	float GetX() { return worldTransform_.matWorld_.m[3][0]; }
	float GetY() { return worldTransform_.matWorld_.m[3][1]; }
	float GetZ() { return worldTransform_.matWorld_.m[3][2]; }

	int GetFlag() { return aliveFlag_; }

	void Hit();

	protected:
	WorldTransform worldTransformBody_;
	    WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	private:
	int aliveFlag_ = 0;

};
