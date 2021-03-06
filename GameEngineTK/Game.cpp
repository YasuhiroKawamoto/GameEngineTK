//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <time.h>



extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;


using Microsoft::WRL::ComPtr;

Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{

	srand(static_cast<unsigned int>(time(nullptr)));

	m_window = window;
	m_outputWidth = std::max(width, 1);
	m_outputHeight = std::max(height, 1);

	CreateDevice();

	CreateResources();


	//// キーボードの生成
	m_keyboard = std::make_unique<Keyboard>();
	m_keyboardTracker = std::make_unique<Keyboard::KeyboardStateTracker>();


	// カメラ生成
	m_camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);


	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/

	// 初期化===================================

	// 3dオブジェクトの静的メンバ変数初期化
	Obj3d::InitializeStatic(m_d3dDevice, m_d3dContext, m_camera.get());

	// プレイヤーの生成
	m_player = std::make_unique<Player>(m_keyboard.get(), m_keyboardTracker.get());

	// プレイヤー初期化
	m_player->Load();
	m_player->Init();
	m_camera->SetPlayer(m_player.get());

	
	// エネミー生成
	int enemyNum = rand() % 10 + 1;

	m_enemies.resize(enemyNum);

	// エネミー初期化
	for (int i = 0; i < enemyNum; i++)
	{
		m_enemies[i] = std::make_unique<Enemy>();
		m_enemies[i]->Load();
		m_enemies[i]->Init();
	}

	m_batch = std::make_unique<PrimitiveBatch<VertexPositionNormal>>(m_d3dContext.Get());

	m_effect = std::make_unique<BasicEffect>(m_d3dDevice.Get());

	m_effect->SetProjection(XMMatrixOrthographicOffCenterRH(0,
		m_outputWidth, m_outputHeight, 0, 0, 1));
	m_effect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.GetAddressOf());

	// 汎用ステートを設定
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	// デバッグカメラを生成
	m_debugCamera = std::make_unique<DebugCamera>(m_outputWidth, m_outputHeight);

	// エフェクトファクトリ生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// テクスチャのパス指定
	m_factory->SetDirectory(L"Resources");
	// モデルの生成
	m_ObjGround.LoadModel(L"Resources\\ground200m.cmo");

	m_ObjSkydome.LoadModel(L"Resources\\SkyDome.cmo");

}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{

	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;

	// 更新====================================
	// デバッグカメラ
	//m_debugCamera->Update();


#pragma region スフィア


	// 行列の計算
	//for (int i = 0; i < Game::SPHERE_NUM; i++)
	//{
	//	// スケーリング
	//	Matrix scalemat = Matrix::CreateScale(1.0f);
	//	m_worldSpehre[i] = scalemat;

	//	Matrix rotmaty;

	//	// 平行移動
	//	Matrix transmat;

	//	if (i >= SPHERE_NUM-1)
	//	{
	//		rotmaty = Matrix::CreateRotationY(XMConvertToRadians(-m_angle));

	//		scalemat = Matrix::CreateScale(2.0f);
	//	}
	//	else if (i < SPHERE_NUM / 2)
	//	{
	//		transmat = Matrix::CreateTranslation( sin(i * XMConvertToRadians(36.0f)) * 20, 0.0f, cos(i * XMConvertToRadians(36.0f)) * 20);

	//		rotmaty = Matrix::CreateRotationY(XMConvertToRadians(m_angle));
	//	}
	//	else
	//	{
	//		transmat = Matrix::CreateTranslation(sin(i * XMConvertToRadians(36.0f)) * 40, 0.0f, cos(i * XMConvertToRadians(36.0f)) * 40);
	//		rotmaty = Matrix::CreateRotationY(XMConvertToRadians(-m_angle));
	//	}
	//	
	//	m_worldSpehre[i] = transmat;
	//	
	//	// 回転
	//	// ロール
	//	// ピッチ
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	//	// ヨー
	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));


	//	// 回転行列の合成
	//	Matrix rotmat = rotmatz* rotmatx * rotmaty;

	//	// ワールド行列の合成()
	//	m_worldSpehre[i] = scalemat *transmat* rotmat ;

	//}

#pragma endregion

	// ポット
	/*
	for (int i = 0; i < Game::POT_NUM; i++)
	{
		//int rnd = rand() % 360;

		//float angle = XMConvertToRadians(static_cast<float>(rnd));

		//// サイズ
		Matrix scalemat = Matrix::CreateScale((sinf(m_angle / 100) + 2.0f)*5.0f);

		//// 座標
		Matrix transmat;

		

		float angle = XMConvertToRadians(static_cast<float>(m_rndAng[i]));

		transmat = Matrix::CreateTranslation((cosf(angle)*m_rndDis[i] *m_time)/600, 0.0f, (sinf(angle)*m_rndDis[i]*m_time) / 600);



		// 回転

		// ロール
		Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
		// ピッチ
		Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
		// ヨー
		Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(m_angle));

		// 回転行列の合成
		Matrix rotmat = rotmatz* rotmatx * rotmaty;

		m_worldPot[i] = scalemat * rotmat *transmat;
	}
	*/

	// プレイヤー更新
	m_player->Update();

	// エネミー更新
	std::vector<std::unique_ptr<Enemy>>::iterator itr;
	for (itr = m_enemies.begin(); itr != m_enemies.end(); itr++)
	{
		(*itr)->Update();
	}
	


	// カメラ切り替え
	if (m_keyboardTracker->pressed.C)
	{
		m_camera->SetMode(m_camera->GetMode()%2+1);
	}

	// カメラ設定(自機追従) 
	{
		m_camera->Update();

		m_view = m_camera->GetView();
		m_proj = m_camera->GetProj();
	}
	m_ObjSkydome.Update();
	m_ObjGround.Update();
}

#pragma region グラウンド

	//// 地面
	//for (int i = 0; i < Game::GROUND_NUM; i++)
	//{
	//	Matrix scalemat = Matrix::CreateScale(1.0f);

	//	Matrix transmat;

	//	transmat = Matrix::CreateTranslation(i % 200-100, 0.f, i / 200 - 100);

	//	// 回転
	//	// ロール

	//	Matrix rotmatz = Matrix::CreateRotationZ(XMConvertToRadians(0.0f));
	//	// ピッチ
	//	Matrix rotmatx = Matrix::CreateRotationX(XMConvertToRadians(0.0f));
	//	// ヨー
	//	Matrix rotmaty = Matrix::CreateRotationY(XMConvertToRadians(0.0f));

	//	// 回転行列の合成
	//	Matrix rotmat = rotmatz* rotmatx * rotmaty;

	//	// ワールド行列の合成()
	//	m_worldGround[i] = scalemat * rotmat *transmat;
	//}
#pragma endregion


// Draws the scene.
void Game::Render()
{

	uint16_t indexes[] =
	{
		0, 1, 2,
		2, 1, 3
	};

	VertexPositionNormal vertices[] =
	{
		{ Vector3(-1.0f,+1.0f, 0.0f),Vector3(0.0f,0.0f, +1.0f) },
		{ Vector3(-1.0f,-1.0f, 0.0f),Vector3(0.0f,0.0f, +1.0f) },
		{ Vector3(+1.0f,+1.0f, 0.0f),Vector3(0.0f,0.0f, +1.0f) },
		{ Vector3(+1.0f,-1.0f, 0.0f),Vector3(0.0f,0.0f, +1.0f) },
	};

	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	// TODO: Add your rendering code here.

	// 描画====================================
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
	m_d3dContext->RSSetState(m_states->Wireframe());
										

	
	m_effect->SetView(m_view);
	m_effect->SetProjection(m_proj);


	m_effect->Apply(m_d3dContext.Get());
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());


	// 実際の描画部分


	m_ObjSkydome.Draw();

	// プレイヤー描画
	m_player->Draw();

	// エネミー描画
	std::vector<std::unique_ptr<Enemy>>::iterator itr;
	for (itr = m_enemies.begin(); itr != m_enemies.end(); itr++)
	{
		(*itr)->Draw();
	}

	m_ObjGround.Draw();


	m_batch->Begin();		// ここから描画=====

	m_batch->End();			// ここまで描画=====


    Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}