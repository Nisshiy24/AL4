#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {

	//NULLポインタチェック
	assert(model);

	//メンバ変数に受け取った値を代入
	model_ = model;

	worldTransform_.Initialize();

}

void Skydome::Update() {}

void Skydome::Draw(const ViewProjection& viewProjection) {

	//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection);

}
