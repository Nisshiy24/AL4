#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
//#include "Model.h"
//#include "Player.h"
//#include "Ground.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();


	////自キャラ生成
	//player_ = new Player();

	
	viewProjection_.farZ = 2000.0f;
	viewProjection_.translation_ = {0.0f, 2.0f, -10.0f};
	viewProjection_.Initialize();



	textureHandle_ = TextureManager::Load("mario.jpg");

	//textureHandleGround_ = TextureManager::Load(" ground.png ");

	//model_.reset(Model::Create());
	modelFighter_.reset(Model::CreateFromOBJ("float", true));
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));

	player_ = std::make_unique<Player>();

	ground_ = std::make_unique<Ground>();

	skydome_ = std::make_unique<Skydome>();

	//自キャラの初期化
	player_->Initialize(modelFighter_.get());

	//グラウンドの初期化
	ground_->Initialize(modelGround_.get());

	//スカイドームの初期化
	skydome_->Initialize(modelSkydome_.get());

}

void GameScene::Update() {

	


}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	ground_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
