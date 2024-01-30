//#include "Beam.h"
//#include "Player.h"
//
//// コンストラクタ
//Beam::Beam() {}
//
//// デストラクタ
//Beam::~Beam() { delete modelBeam_; }
//
//// 初期化
//void Beam::Initialize(ViewProjection viewProjection, Player* player) {
//
//	viewProjection_ = viewProjection;
//
//	textureHandleBeam_ = TextureManager::Load("beam.png");
//	modelBeam_ = Model::Create();
//	worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
//	worldTransformBeam_.Initialize();
//	player_ = player;
//
//	input_ = Input::GetInstance();
//}
//
//// 更新
//void Beam::Update() {
//
//	// 移動
//	Move();
//
//	// 発生（発射）
//	Born();
//
//	worldTransformBeam_.matWorld_ = MakeAffineMatrix(
//	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
//	    worldTransformBeam_.translation_);
//
//	worldTransformBeam_.TransferMatrix();
//}
//
//// ３D描画
//void Beam::Draw3D() {
//
//	if (aliveFlag_ == 1) {
//		modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
//	}
//}
//
//// 移動
//void Beam::Move() {
//
//	if (aliveFlag_ == 1) {
//		worldTransformBeam_.translation_.z += 0.3f;
//	}
//	worldTransformBeam_.rotation_.x += 0.1f;
//}
//
//// 発生
//void Beam::Born() {
//
//	if (input_->PushKey(DIK_SPACE)) {
//
//		if (aliveFlag_ == 0) {
//
//			worldTransformBeam_.translation_.x = player_->GetX();
//			worldTransformBeam_.translation_.y = 0;
//			worldTransformBeam_.translation_.z = 0;
//
//			aliveFlag_ = 1;
//		}
//	}
//
//	if (worldTransformBeam_.translation_.z > 40) {
//		aliveFlag_ = 0;
//	}
//}