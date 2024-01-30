#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <AxisIndicator.h>
#include "MathUtilityForText.h"
#include "ImGuiManager.h"

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

		modelFighterBody_.reset(Model::CreateFromOBJ("player1_body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("player1_head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("player1_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("player1_R_arm", true));

	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));


	modelEnemyBody_.reset(Model::CreateFromOBJ("player_head", true));
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("player_L_arm", true));
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("player_R_arm", true));


	player_ = std::make_unique<Player>();

	ground_ = std::make_unique<Ground>();

	skydome_ = std::make_unique<Skydome>();


	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get()

	};

	player_->Initialize(playerModels);
	

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


	//敵のモデル
	std::vector<Model*> enemyModels = {
	    modelEnemyBody_.get(), modelEnemyL_arm_.get(), modelEnemyR_arm_.get()};

	enemy_ = std::make_unique<Enemy>();
	//敵の初期化
	enemy_->Initialize(enemyModels);
	enemy_->SetLocalPosition(Vector3(10, 0, 20));
	enemy_->SetLocalRotation(Vector3(0, PI, 0));


	
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();


	textureHandleBlack_ = TextureManager::Load("black.png");
	spriteBlack_ = Sprite::Create(textureHandleBlack_, {0, 0});

	 texturehandleTitleEnter_ = TextureManager::Load("tap to enter.png");
	spriteTitleEnter_ = Sprite::Create(texturehandleTitleEnter_, {0, 0});

	 texturehandlebackground_ = TextureManager::Load("universe.png");
	spritebackground_ = Sprite::Create(texturehandlebackground_, {0, 0});

	 texturehandletitle_ = TextureManager::Load("spaceattack.png");
	spritebacktitle_ = Sprite::Create(texturehandletitle_, {0, 0});


	 texturehandlerulu_ = TextureManager::Load("gamerulu.png");
	spriterulu_ = Sprite::Create(texturehandlerulu_, {0, 0});

	 texturehandlescore_ = TextureManager::Load("score.png");
	spritescore_ = Sprite::Create(texturehandlescore_, {0, 0});




	 texturehandlescore0_ = TextureManager::Load("score0.png");
	spritescore0_ = Sprite::Create(texturehandlescore0_, {0, 0});

	 texturehandlescore100_ = TextureManager::Load("score100.png");
	spritescore100_ = Sprite::Create(texturehandlescore100_, {0, 0});

	 texturehandlescore200_ = TextureManager::Load("score200.png");
	spritescore200_ = Sprite::Create(texturehandlescore200_, {0, 0});

	 texturehandlescore300_ = TextureManager::Load("score300.png");
	spritescore300_ = Sprite::Create(texturehandlescore300_, {0, 0});

	 texturehandlescore400_ = TextureManager::Load("score400.png");
	spritescore400_ = Sprite::Create(texturehandlescore400_, {0, 0});

	 texturehandlescore500_ = TextureManager::Load("score500.png");
	spritescore500_ = Sprite::Create(texturehandlescore500_, {0, 0});

	 texturehandlescore600_ = TextureManager::Load("score600.png");
	spritescore600_ = Sprite::Create(texturehandlescore600_, {0, 0});

	 texturehandlescore700_ = TextureManager::Load("score700.png");
	spritescore700_ = Sprite::Create(texturehandlescore700_, {0, 0});

	 texturehandlescore800_ = TextureManager::Load("score800.png");
	spritescore800_ = Sprite::Create(texturehandlescore800_, {0, 0});

	 texturehandlescore900_ = TextureManager::Load("score900.png");
	spritescore900_ = Sprite::Create(texturehandlescore900_, {0, 0});

	 texturehandlescore1000_ = TextureManager::Load("score1000.png");
	spritescore1000_ = Sprite::Create(texturehandlescore1000_, {0, 0});

	 texturehandlescore1100_ = TextureManager::Load("score1100.png");
	spritescore1100_ = Sprite::Create(texturehandlescore1100_, {0, 0});

	 texturehandlescore1200_ = TextureManager::Load("score1200.png");
	spritescore1200_ = Sprite::Create(texturehandlescore1200_, {0, 0});

	 texturehandlescore1300_ = TextureManager::Load("score1300.png");
	spritescore1300_ = Sprite::Create(texturehandlescore1300_, {0, 0});

	 texturehandlescore1400_ = TextureManager::Load("score1400.png");
	spritescore1400_ = Sprite::Create(texturehandlescore1400_, {0, 0});

	 texturehandlescore1500_ = TextureManager::Load("score1500.png");
	spritescore1500_ = Sprite::Create(texturehandlescore1500_, {0, 0});





}

void GameScene::Title() { 

	    if (input_->TriggerKey(DIK_RETURN)) {
		flag_ = true;

		black = 0;
	    }
	    if (flag_ == true && black >= 1.0f) {
		flag_ = false;
		black = 1.0f;
		scenmode = 1;
	    }

		titletimer++;
	    GameStar();

	}

void GameScene::Rulu() {

		if (input_->TriggerKey(DIK_RETURN)) {
		flag_ = true;

		black = 0;
	    }
	    if (flag_ == true && black >= 1.0f) {
		flag_ = false;
		black = 1.0f;
		scenmode = 2;
	    }


    }

void GameScene::GamePlay() {

	// デバックカメラの更新
	    if (input_->TriggerKey(DIK_0)) {
		// フラグをトグル
		isDebugCameraActive_ = !isDebugCameraActive_;
	    }
	    if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
	    } else {
		fllowCamera_->Update();
		viewProjection_.matView = fllowCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = fllowCamera_->GetViewProjection().matProjection;
	    }

	    // ビュープロジェクションの転送
	    viewProjection_.TransferMatrix();

	    player_->Update();

	    enemy_->Update();

	    if (enemy_->GetFlag() == 1) {
		float dx = abs(player_->GetX() - enemy_->GetX());
		float dz = abs(player_->GetZ() - enemy_->GetZ());

		if (dx < 2 && dz < 2) {
			enemy_->Hit();
			score += 1;
		}
	    }

	   

		enemy_->UpdateGimmick();

	if (gametimer == 0)
	{
		flag_ = true;
		black = 0;
	}

	 if (flag_ == true && black >= 1.0f) {
		flag_ = false;
		black = 1.0f;
		scenmode = 3;
	}

}

void GameScene::GameClear() {

		if (input_->TriggerKey(DIK_RETURN)) {
		flag_ = true;

		black = 0;
	    }
	    if (flag_ == true && black >= 1.0f) {
		flag_ = false;
		black = 1.0f;
		scenmode = 0;
	    }
}

void GameScene::GameStar() {

	gametimer = 2000;
	score = 0;

}

void GameScene::Update() {

	switch (scenmode) {
	case 0:
		Title();
		
		break;
	case 1:
		Rulu();
		break;
	case 2:
		GamePlay();
		gametimer--;
		break;
	case 3:
		GameClear();
		break;
	
	}





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
	switch (scenmode) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		spritebackground_->Draw();
		break;
	case 3:
		break;
	}
	

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

	switch (scenmode) {
	case 0:
		
		break;
	case 1:

		break;
	case 2:
		player_->Draw(viewProjection_);
		
		enemy_->Draw(viewProjection_);
		break;
	case 3:

		break;

	}

	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	switch (scenmode) {
	case 0:
		debugText_->Print("title", 0, 0, 3);
		spritebackground_->Draw();
		spritebacktitle_->Draw();
		if (titletimer % 40 >= 20) {
			
			spriteTitleEnter_->Draw();
		}
		break;
	case 1:
		spritebackground_->Draw();
		spriterulu_->Draw();
		debugText_->Print("rulu", 50, 50, 3);
		break;
	case 2:
		
		char str[1000];
		sprintf_s(str, "Timer %d", gametimer);
		debugText_->Print(str, 50, 50, 3);

		sprintf_s(str, "Score %d", score);
		debugText_->Print(str, 50, 200, 3);
		break;
		break;
	case 3:
		spritebackground_->Draw();

		if (score == 0)
		{
			spritescore0_->Draw();
		}

		if (score == 1) {
			spritescore100_->Draw();
		}

		if (score == 2) {
			spritescore200_->Draw();
		}

		if (score == 3) {
			spritescore300_->Draw();
		}

		if (score == 4) {
			spritescore400_->Draw();
		}

		if (score == 5) {
			spritescore500_->Draw();
		}

		if (score == 6) {
			spritescore600_->Draw();
		}

		if (score == 7) {
			spritescore700_->Draw();
		}

		if (score == 8) {
			spritescore800_->Draw();
		}

		if (score == 9) {
			spritescore900_->Draw();
		}

		if (score == 10) {
			spritescore1000_->Draw();
		}

		if (score == 11) {
			spritescore1100_->Draw();
		}

		if (score == 12) {
			spritescore1200_->Draw();
		}

		if (score == 13) {
			spritescore1300_->Draw();
		}

		if (score == 14) {
			spritescore1400_->Draw();
		}

		if (score >= 15) {
			spritescore1500_->Draw();
		}

		spritescore_->Draw();
		debugText_->Print("gameclear", 50, 50, 3);
		break;
	}

	if (flag_ == false) {
		black -= 0.01f;
	} else {
		black += 0.01f;
	}

	spriteBlack_->SetColor({1, 1, 1, black});
	spriteBlack_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
