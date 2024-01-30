#include "Player.h"
#include <cassert>
#include "ImGuiManager.h"
#include "Vector3.h"
#include <MathUtilityForText.h>

//#include "ViewProjection.h"

void Player::Initialize(const std::vector<Model*>& models) {
	
	//基礎クラスの初期化
	BaseCharacter::Initialize(models);


//assert(model);
//assert(modelBody);
//assert(modelHead);
//assert(modelL_arm);
//assert(modelR_arm);

//textureHandle_ = textureHandle;
//model_ = model;

//modelFighterBody_ = modelBody;
//modelFighterHead_ = modelHead;
//modelFighterL_arm_ = modelL_arm;
//modelFighterR_arm_ = modelR_arm;

worldTransform_.Initialize();
worldTransformBody_.Initialize();
worldTransformHead_.Initialize();
worldTransformL_arm_.Initialize();
worldTransformR_arm_.Initialize();


//親子構造
worldTransformBody_.parent_ = &worldTransform_;
worldTransformHead_.parent_ = &worldTransformBody_;
worldTransformL_arm_.parent_ = &worldTransformBody_;
worldTransformR_arm_.parent_ = &worldTransformBody_;


//位置調整
worldTransformHead_.translation_.y = 0.3038f;
worldTransformL_arm_.translation_.x = -0.1275f;
worldTransformL_arm_.translation_.y = 0.2619f;
worldTransformR_arm_.translation_.x = +0.1275f;
worldTransformR_arm_.translation_.y = 0.2619f;



input_ = Input::GetInstance();

InitializeFloatingGimmick();

}

void Player::Update() {  
	UpdateFloatingGimmick();
	const float speed = 0.3f;
Vector3 move = {0.0f, 0.0f, 0.0f};
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
	move.x = 1.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
	move.x = -1.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_UP)) {
	move.z = 1.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_DOWN)) {
	move.z = -1.0f;
	}

	move = Normalize(move) * speed;



	if (viewProjection_)
	{
		//カメラの回転行列
	Matrix4x4 matRotX = MakeRotateXMatrix(viewProjection_->rotation_.x);
	Matrix4x4 matRotY = MakeRotateYMatrix(viewProjection_->rotation_.y);
	Matrix4x4 matRotZ = MakeRotateZMatrix(viewProjection_->rotation_.z);
		

	//回転行列の合成
	Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	//移動量をカメラの回転に合わせて回転させる
	move = TransformNormal(move, matRot);

	}

	worldTransform_.translation_ += move;

	//移動ベクトルのY軸周り角度
	worldTransform_.rotation_.y = std::atan2(move.x, move.z);

	//変換行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	                                             // 変換行列を定数バッファに転送
  worldTransform_.TransferMatrix();

												 

  worldTransform_.UpdateMatrix();
  worldTransformBody_.UpdateMatrix();
 worldTransformHead_.UpdateMatrix();
worldTransformL_arm_.UpdateMatrix();
 worldTransformR_arm_.UpdateMatrix();
	

}

void Player::Draw(const ViewProjection& viewProjection) {

	//model_->Draw(worldTransform_, viewProjection);
	/*modelFighterBody_->Draw(worldTransformBody_, viewProjection);
	modelFighterHead_->Draw(worldTransformHead_, viewProjection);
	modelFighterL_arm_->Draw(worldTransformL_arm_, viewProjection);
	modelFighterR_arm_->Draw(worldTransformR_arm_, viewProjection);*/

models_[kModelIndexBody]->Draw(worldTransformBody_, viewProjection);
 models_[kModelIndexHead]->Draw(worldTransformHead_, viewProjection);
models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, viewProjection);
 models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, viewProjection);


}

void Player::InitializeFloatingGimmick() { 
	floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() {
	//最もシンプルなアニメーション処理
	floatingParameter_ += 0.1f;
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * 0.2f;
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * 0.5f;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * 0.5f;

}


