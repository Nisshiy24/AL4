#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <AxisIndicator.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.farZ = 2000.0f;
	viewProjection_.translation_ = {0.0f, 2.0f, -10.0f};
	viewProjection_.Initialize();



	textureHandle_ = TextureManager::Load("mario.jpg");

	
	modelFighter_.reset(Model::CreateFromOBJ("monster", true));

	modelGround_.reset(Model::CreateFromOBJ("ground2", true));

	modelSkydome_.reset(Model::CreateFromOBJ("skydome2", true));

	player_ = std::make_unique<Player>();

	ground_ = std::make_unique<Ground>();

	skydome_ = std::make_unique<Skydome>();

	//自キャラの初期化
	player_->Initialize(modelFighter_.get());

	//グラウンドの初期化
	ground_->Initialize(modelGround_.get());

	//スカイドームの初期化
	skydome_->Initialize(modelSkydome_.get());



	//デバックカメラ
	debugCamera_ = std::make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
	debugCamera_->SetFarZ(2000.0f);

	//追従カメラ
	fllowCamera_ = std::make_unique<FollowCamera>();
	fllowCamera_->Initialize();

	player_->SetViewProjection(&fllowCamera_->GetViewProjection());

	//自キャラのワールドトランスフォームを追従カメラにセット
	fllowCamera_->SetTarget(&player_->GetWorldTransform());

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);

	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());



}

void GameScene::Update() {

//デバックカメラの更新
	if (input_->TriggerKey(DIK_0))
	{
		//フラグをトグル
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
	if (isDebugCameraActive_ == true)
	{
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
	} else {
		fllowCamera_->Update();
		viewProjection_.matView = fllowCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = fllowCamera_->GetViewProjection().matProjection;
	}

	//ビュープロジェクションの転送
	viewProjection_.TransferMatrix();

	player_->Update();


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
