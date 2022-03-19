/** @file GAME3111_LiIngram_A1.cpp
 *  @Assignment 1 for Adv Graphics Programming.
 *
 *
 *
 *   Controls:
 *   Hold down '1' key to view scene in wireframe mode.
 *   Hold the left mouse button down and move the mouse to rotate.
 *   Hold the right mouse button down and move the mouse to zoom in and out.
 *
 *  @author Russell Li, Zackary Ingram
 */


#include "../Common/d3dApp.h"
#include "../Common/MathHelper.h"
#include "../Common/UploadBuffer.h"
#include "../Common/GeometryGenerator.h"
#include "FrameResource.h"

//using Microsoft::WRL::ComPtr;
//using namespace DirectX;
//using namespace DirectX::PackedVector;
//
//const int gNumFrameResources = 3;
//
//// Lightweight structure stores parameters to draw a shape.  This will
//// vary from app-to-app.
//struct RenderItem
//{
//	RenderItem() = default;
//
//	// World matrix of the shape that describes the object's local space
//	// relative to the world space, which defines the position, orientation,
//	// and scale of the object in the world.
//	XMFLOAT4X4 World = MathHelper::Identity4x4();
//
//	// Dirty flag indicating the object data has changed and we need to update the constant buffer.
//	// Because we have an object cbuffer for each FrameResource, we have to apply the
//	// update to each FrameResource.  Thus, when we modify obect data we should set 
//	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
//	int NumFramesDirty = gNumFrameResources;
//
//	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
//	UINT ObjCBIndex = -1;
//
//	MeshGeometry* Geo = nullptr;
//
//	// Primitive topology.
//	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//
//	// DrawIndexedInstanced parameters.
//	UINT IndexCount = 0;
//	UINT StartIndexLocation = 0;
//	int BaseVertexLocation = 0;
//};
//
//class ShapesApp : public D3DApp
//{
//public:
//	ShapesApp(HINSTANCE hInstance);
//	ShapesApp(const ShapesApp& rhs) = delete;
//	ShapesApp& operator=(const ShapesApp& rhs) = delete;
//	~ShapesApp();
//
//	virtual bool Initialize()override;
//
//private:
//	virtual void OnResize()override;
//	virtual void Update(const GameTimer& gt)override;
//	virtual void Draw(const GameTimer& gt)override;
//
//	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
//	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
//	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;
//
//	void OnKeyboardInput(const GameTimer& gt);
//	void UpdateCamera(const GameTimer& gt);
//	void UpdateObjectCBs(const GameTimer& gt);
//	void UpdateMainPassCB(const GameTimer& gt);
//
//	void BuildDescriptorHeaps();
//	void BuildConstantBufferViews();
//	void BuildRootSignature();
//	void BuildShadersAndInputLayout();
//	void BuildShapeGeometry();
//	void BuildPSOs();
//	void BuildFrameResources();
//	void BuildRenderItems();
//	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
//
//private:
//
//	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
//	FrameResource* mCurrFrameResource = nullptr;
//	int mCurrFrameResourceIndex = 0;
//
//	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
//	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;
//
//	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;
//
//	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
//	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
//	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
//
//	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
//
//	// List of all the render items.
//	std::vector<std::unique_ptr<RenderItem>> mAllRitems;
//
//	// Render items divided by PSO.
//	std::vector<RenderItem*> mOpaqueRitems;
//
//	PassConstants mMainPassCB;
//
//	UINT mPassCbvOffset = 0;
//
//	bool mIsWireframe = false;
//
//	XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
//	XMFLOAT4X4 mView = MathHelper::Identity4x4();
//	XMFLOAT4X4 mProj = MathHelper::Identity4x4();
//
//	float mTheta = 1.5f * XM_PI;
//	float mPhi = 0.2f * XM_PI;
//	float mRadius = 100.0f;
//
//	POINT mLastMousePos;
//};
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
//	PSTR cmdLine, int showCmd)
//{
//	// Enable run-time memory check for debug builds.
//#if defined(DEBUG) | defined(_DEBUG)
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//
//	try
//	{
//		ShapesApp theApp(hInstance);
//		if (!theApp.Initialize())
//			return 0;
//
//		return theApp.Run();
//	}
//	catch (DxException& e)
//	{
//		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
//		return 0;
//	}
//}
//
//ShapesApp::ShapesApp(HINSTANCE hInstance)
//	: D3DApp(hInstance)
//{
//}
//
//ShapesApp::~ShapesApp()
//{
//	if (md3dDevice != nullptr)
//		FlushCommandQueue();
//}
//
//bool ShapesApp::Initialize()
//{
//	if (!D3DApp::Initialize())
//		return false;
//
//	// Reset the command list to prep for initialization commands.
//	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));
//
//	BuildRootSignature();
//	BuildShadersAndInputLayout();
//	BuildShapeGeometry();
//	BuildRenderItems();
//	BuildFrameResources();
//	BuildDescriptorHeaps();
//	BuildConstantBufferViews();
//	BuildPSOs();
//
//	// Execute the initialization commands.
//	ThrowIfFailed(mCommandList->Close());
//	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
//	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
//
//	// Wait until initialization is complete.
//	FlushCommandQueue();
//
//	return true;
//}
//
//void ShapesApp::OnResize()
//{
//	D3DApp::OnResize();
//
//	// The window resized, so update the aspect ratio and recompute the projection matrix.
//	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
//	XMStoreFloat4x4(&mProj, P);
//}
//
//void ShapesApp::Update(const GameTimer& gt)
//{
//	OnKeyboardInput(gt);
//	UpdateCamera(gt);
//
//	// Cycle through the circular frame resource array.
//	mCurrFrameResourceIndex = (mCurrFrameResourceIndex + 1) % gNumFrameResources;
//	mCurrFrameResource = mFrameResources[mCurrFrameResourceIndex].get();
//
//	// Has the GPU finished processing the commands of the current frame resource?
//	// If not, wait until the GPU has completed commands up to this fence point.
//	if (mCurrFrameResource->Fence != 0 && mFence->GetCompletedValue() < mCurrFrameResource->Fence)
//	{
//		HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);
//		ThrowIfFailed(mFence->SetEventOnCompletion(mCurrFrameResource->Fence, eventHandle));
//		WaitForSingleObject(eventHandle, INFINITE);
//		CloseHandle(eventHandle);
//	}
//
//	UpdateObjectCBs(gt);
//	UpdateMainPassCB(gt);
//}
//
//void ShapesApp::Draw(const GameTimer& gt)
//{
//	auto cmdListAlloc = mCurrFrameResource->CmdListAlloc;
//
//	// Reuse the memory associated with command recording.
//	// We can only reset when the associated command lists have finished execution on the GPU.
//	ThrowIfFailed(cmdListAlloc->Reset());
//
//	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
//	// Reusing the command list reuses memory.
//	if (mIsWireframe)
//	{
//		ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(), mPSOs["opaque_wireframe"].Get()));
//	}
//	else
//	{
//		ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(), mPSOs["opaque"].Get()));
//	}
//
//	mCommandList->RSSetViewports(1, &mScreenViewport);
//	mCommandList->RSSetScissorRects(1, &mScissorRect);
//
//	// Indicate a state transition on the resource usage.
//	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
//		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
//
//	// Clear the back buffer and depth buffer.
//	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
//	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
//
//	// Specify the buffers we are going to render to.
//	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
//
//	ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvHeap.Get() };
//	mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
//
//	mCommandList->SetGraphicsRootSignature(mRootSignature.Get());
//
//	int passCbvIndex = mPassCbvOffset + mCurrFrameResourceIndex;
//	auto passCbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
//	passCbvHandle.Offset(passCbvIndex, mCbvSrvUavDescriptorSize);
//	mCommandList->SetGraphicsRootDescriptorTable(1, passCbvHandle);
//
//	DrawRenderItems(mCommandList.Get(), mOpaqueRitems);
//
//	// Indicate a state transition on the resource usage.
//	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
//		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
//
//	// Done recording commands.
//	ThrowIfFailed(mCommandList->Close());
//
//	// Add the command list to the queue for execution.
//	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
//	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
//
//	// Swap the back and front buffers
//	ThrowIfFailed(mSwapChain->Present(0, 0));
//	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;
//
//	// Advance the fence value to mark commands up to this fence point.
//	mCurrFrameResource->Fence = ++mCurrentFence;
//
//	// Add an instruction to the command queue to set a new fence point. 
//	// Because we are on the GPU timeline, the new fence point won't be 
//	// set until the GPU finishes processing all the commands prior to this Signal().
//	mCommandQueue->Signal(mFence.Get(), mCurrentFence);
//}
//
//void ShapesApp::OnMouseDown(WPARAM btnState, int x, int y)
//{
//	mLastMousePos.x = x;
//	mLastMousePos.y = y;
//
//	SetCapture(mhMainWnd);
//}
//
//void ShapesApp::OnMouseUp(WPARAM btnState, int x, int y)
//{
//	ReleaseCapture();
//}
//
//void ShapesApp::OnMouseMove(WPARAM btnState, int x, int y)
//{
//	if ((btnState & MK_LBUTTON) != 0)
//	{
//		// Make each pixel correspond to a quarter of a degree.
//		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
//		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));
//
//		// Update angles based on input to orbit camera around box.
//		mTheta += dx;
//		mPhi += dy;
//
//		// Restrict the angle mPhi.
//		mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
//	}
//	else if ((btnState & MK_RBUTTON) != 0)
//	{
//		// Make each pixel correspond to 0.2 unit in the scene.
//		float dx = 0.05f * static_cast<float>(x - mLastMousePos.x);
//		float dy = 0.05f * static_cast<float>(y - mLastMousePos.y);
//
//		// Update the camera radius based on input.
//		mRadius += dx - dy;
//
//		// Restrict the radius.
//		mRadius = MathHelper::Clamp(mRadius, 5.0f, 150.0f);
//	}
//
//	mLastMousePos.x = x;
//	mLastMousePos.y = y;
//}
//
//void ShapesApp::OnKeyboardInput(const GameTimer& gt)
//{
//	if (GetAsyncKeyState('1') & 0x8000)
//		mIsWireframe = true;
//	else
//		mIsWireframe = false;
//}
//
//void ShapesApp::UpdateCamera(const GameTimer& gt)
//{
//	// Convert Spherical to Cartesian coordinates.
//	mEyePos.x = mRadius * sinf(mPhi) * cosf(mTheta);
//	mEyePos.z = mRadius * sinf(mPhi) * sinf(mTheta);
//	mEyePos.y = mRadius * cosf(mPhi);
//
//	// Build the view matrix.
//	XMVECTOR pos = XMVectorSet(mEyePos.x, mEyePos.y, mEyePos.z, 1.0f);
//	XMVECTOR target = XMVectorZero();
//	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//
//	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
//	XMStoreFloat4x4(&mView, view);
//}
//
//void ShapesApp::UpdateObjectCBs(const GameTimer& gt)
//{
//	auto currObjectCB = mCurrFrameResource->ObjectCB.get();
//	for (auto& e : mAllRitems)
//	{
//		// Only update the cbuffer data if the constants have changed.  
//		// This needs to be tracked per frame resource.
//		if (e->NumFramesDirty > 0)
//		{
//			XMMATRIX world = XMLoadFloat4x4(&e->World);
//
//			ObjectConstants objConstants;
//			XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
//
//			currObjectCB->CopyData(e->ObjCBIndex, objConstants);
//
//			// Next FrameResource need to be updated too.
//			e->NumFramesDirty--;
//		}
//	}
//}
//
//void ShapesApp::UpdateMainPassCB(const GameTimer& gt)
//{
//	XMMATRIX view = XMLoadFloat4x4(&mView);
//	XMMATRIX proj = XMLoadFloat4x4(&mProj);
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
//	XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
//	XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);
//
//	XMStoreFloat4x4(&mMainPassCB.View, XMMatrixTranspose(view));
//	XMStoreFloat4x4(&mMainPassCB.InvView, XMMatrixTranspose(invView));
//	XMStoreFloat4x4(&mMainPassCB.Proj, XMMatrixTranspose(proj));
//	XMStoreFloat4x4(&mMainPassCB.InvProj, XMMatrixTranspose(invProj));
//	XMStoreFloat4x4(&mMainPassCB.ViewProj, XMMatrixTranspose(viewProj));
//	XMStoreFloat4x4(&mMainPassCB.InvViewProj, XMMatrixTranspose(invViewProj));
//	mMainPassCB.EyePosW = mEyePos;
//	mMainPassCB.RenderTargetSize = XMFLOAT2((float)mClientWidth, (float)mClientHeight);
//	mMainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / mClientWidth, 1.0f / mClientHeight);
//	mMainPassCB.NearZ = 1.0f;
//	mMainPassCB.FarZ = 1000.0f;
//	mMainPassCB.TotalTime = gt.TotalTime();
//	mMainPassCB.DeltaTime = gt.DeltaTime();
//
//	auto currPassCB = mCurrFrameResource->PassCB.get();
//	currPassCB->CopyData(0, mMainPassCB);
//}
//
//void ShapesApp::BuildDescriptorHeaps()
//{
//	UINT objCount = (UINT)mOpaqueRitems.size();
//
//	// Need a CBV descriptor for each object for each frame resource,
//	// +1 for the perPass CBV for each frame resource.
//	UINT numDescriptors = (objCount + 1) * gNumFrameResources;
//
//	// Save an offset to the start of the pass CBVs.  These are the last 3 descriptors.
//	mPassCbvOffset = objCount * gNumFrameResources;
//
//	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
//	cbvHeapDesc.NumDescriptors = numDescriptors;
//	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
//	cbvHeapDesc.NodeMask = 0;
//	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&cbvHeapDesc,
//		IID_PPV_ARGS(&mCbvHeap)));
//}
//
//void ShapesApp::BuildConstantBufferViews()
//{
//	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
//
//	UINT objCount = (UINT)mOpaqueRitems.size();
//
//	// Need a CBV descriptor for each object for each frame resource.
//	for (int frameIndex = 0; frameIndex < gNumFrameResources; ++frameIndex)
//	{
//		auto objectCB = mFrameResources[frameIndex]->ObjectCB->Resource();
//		for (UINT i = 0; i < objCount; ++i)
//		{
//			D3D12_GPU_VIRTUAL_ADDRESS cbAddress = objectCB->GetGPUVirtualAddress();
//
//			// Offset to the ith object constant buffer in the buffer.
//			cbAddress += i * objCBByteSize;
//
//			// Offset to the object cbv in the descriptor heap.
//			int heapIndex = frameIndex * objCount + i;
//			auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
//			handle.Offset(heapIndex, mCbvSrvUavDescriptorSize);
//
//			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//			cbvDesc.BufferLocation = cbAddress;
//			cbvDesc.SizeInBytes = objCBByteSize;
//
//			md3dDevice->CreateConstantBufferView(&cbvDesc, handle);
//		}
//	}
//
//	UINT passCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(PassConstants));
//
//	// Last three descriptors are the pass CBVs for each frame resource.
//	for (int frameIndex = 0; frameIndex < gNumFrameResources; ++frameIndex)
//	{
//		auto passCB = mFrameResources[frameIndex]->PassCB->Resource();
//		D3D12_GPU_VIRTUAL_ADDRESS cbAddress = passCB->GetGPUVirtualAddress();
//
//		// Offset to the pass cbv in the descriptor heap.
//		int heapIndex = mPassCbvOffset + frameIndex;
//		auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
//		handle.Offset(heapIndex, mCbvSrvUavDescriptorSize);
//
//		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
//		cbvDesc.BufferLocation = cbAddress;
//		cbvDesc.SizeInBytes = passCBByteSize;
//
//		md3dDevice->CreateConstantBufferView(&cbvDesc, handle);
//	}
//}
//
//void ShapesApp::BuildRootSignature()
//{
//	CD3DX12_DESCRIPTOR_RANGE cbvTable0;
//	cbvTable0.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
//
//	CD3DX12_DESCRIPTOR_RANGE cbvTable1;
//	cbvTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);
//
//	// Root parameter can be a table, root descriptor or root constants.
//	CD3DX12_ROOT_PARAMETER slotRootParameter[2];
//
//	// Create root CBVs.
//	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable0);
//	slotRootParameter[1].InitAsDescriptorTable(1, &cbvTable1);
//
//	// A root signature is an array of root parameters.
//	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(2, slotRootParameter, 0, nullptr,
//		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
//
//	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
//	ComPtr<ID3DBlob> serializedRootSig = nullptr;
//	ComPtr<ID3DBlob> errorBlob = nullptr;
//	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
//		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());
//
//	if (errorBlob != nullptr)
//	{
//		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
//	}
//	ThrowIfFailed(hr);
//
//	ThrowIfFailed(md3dDevice->CreateRootSignature(
//		0,
//		serializedRootSig->GetBufferPointer(),
//		serializedRootSig->GetBufferSize(),
//		IID_PPV_ARGS(mRootSignature.GetAddressOf())));
//}
//
//void ShapesApp::BuildShadersAndInputLayout()
//{
//	mShaders["standardVS"] = d3dUtil::CompileShader(L"Shaders\\VS.hlsl", nullptr, "VS", "vs_5_1");
//	mShaders["opaquePS"] = d3dUtil::CompileShader(L"Shaders\\PS.hlsl", nullptr, "PS", "ps_5_1");
//
//	mInputLayout =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
//		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
//	};
//}
//
//
//void ShapesApp::BuildShapeGeometry()
//{//
//	GeometryGenerator geoGen;
//	GeometryGenerator::MeshData box = geoGen.CreateBox(1.0f, 1.0f, 1.0f, 0);
//	GeometryGenerator::MeshData grid = geoGen.CreateGrid(100.0f, 100.0f, 60, 40);
//	GeometryGenerator::MeshData sphere = geoGen.CreateSphere(12.0f, 20, 20);
//	//GeometryGenerator::MeshData sphere2 = geoGen.CreateSphere(6.0f, 20, 20);
//	GeometryGenerator::MeshData cylinder = geoGen.CreateCylinder(10.0f, 10.0f, 30.0f, 20, 20);
//	GeometryGenerator::MeshData cone = geoGen.CreateCylinder(15.0f, 0.0f, 10.0f, 20, 20);
//
//	// We are concatenating all the geometry into one big vertex/index buffer.  So
//	// define the regions in the buffer each submesh covers.
//
//	// Cache the vertex offsets to each object in the concatenated vertex buffer.
//	UINT boxVertexOffset = 0;
//	UINT gridVertexOffset = (UINT)box.Vertices.size();
//	UINT sphereVertexOffset = gridVertexOffset + (UINT)grid.Vertices.size();
//	//UINT sphereVertexOffset2 = gridVertexOffset + (UINT)grid.Vertices.size();
//	UINT cylinderVertexOffset = sphereVertexOffset + (UINT)sphere.Vertices.size();
//	UINT coneVertexOffset = sphereVertexOffset + (UINT)sphere.Vertices.size();
//
//	// Cache the starting index for each object in the concatenated index buffer.
//	UINT boxIndexOffset = 0;
//	UINT gridIndexOffset = (UINT)box.Indices32.size();
//	UINT sphereIndexOffset = gridIndexOffset + (UINT)grid.Indices32.size();
//	//UINT sphereIndexOffset2 = gridIndexOffset + (UINT)grid.Indices32.size();
//	UINT cylinderIndexOffset = sphereIndexOffset + (UINT)sphere.Indices32.size();
//	UINT coneIndexOffset = sphereIndexOffset + (UINT)sphere.Indices32.size();
//
//	// Define the SubmeshGeometry that cover different
//	// regions of the vertex/index buffers.
//
//	SubmeshGeometry boxSubmesh;
//	boxSubmesh.IndexCount = (UINT)box.Indices32.size();
//	boxSubmesh.StartIndexLocation = boxIndexOffset;
//	boxSubmesh.BaseVertexLocation = boxVertexOffset;
//
//	SubmeshGeometry gridSubmesh;
//	gridSubmesh.IndexCount = (UINT)grid.Indices32.size();
//	gridSubmesh.StartIndexLocation = gridIndexOffset;
//	gridSubmesh.BaseVertexLocation = gridVertexOffset;
//
//	SubmeshGeometry sphereSubmesh;
//	sphereSubmesh.IndexCount = (UINT)sphere.Indices32.size();
//	sphereSubmesh.StartIndexLocation = sphereIndexOffset;
//	sphereSubmesh.BaseVertexLocation = sphereVertexOffset;
//
//	/*SubmeshGeometry sphereSubmesh2;
//	sphereSubmesh2.IndexCount = (UINT)sphere2.Indices32.size();
//	sphereSubmesh2.StartIndexLocation = sphereIndexOffset2;
//	sphereSubmesh2.BaseVertexLocation = sphereVertexOffset2;*/
//
//	SubmeshGeometry cylinderSubmesh;
//	cylinderSubmesh.IndexCount = (UINT)cylinder.Indices32.size();
//	cylinderSubmesh.StartIndexLocation = cylinderIndexOffset;
//	cylinderSubmesh.BaseVertexLocation = cylinderVertexOffset;
//
//	SubmeshGeometry coneSubmesh;
//	coneSubmesh.IndexCount = (UINT)cone.Indices32.size();
//	coneSubmesh.StartIndexLocation = coneIndexOffset;
//	coneSubmesh.BaseVertexLocation = coneVertexOffset;
//
//	// Extract the vertex elements we are interested in and pack the
//	// vertices of all the meshes into one vertex buffer.
//
//	auto totalVertexCount =
//		box.Vertices.size() +
//		grid.Vertices.size() +
//		sphere.Vertices.size() +
//		//sphere2.Vertices.size() +
//		cylinder.Vertices.size() +
//		cone.Vertices.size();
//
//
//	std::vector<Vertex> vertices(totalVertexCount);
//
//	UINT k = 0;
//
//	for (size_t i = 0; i < box.Vertices.size(); ++i, ++k)
//	{
//		vertices[k].Pos = box.Vertices[i].Position;
//		//vertices[k].Color = XMFLOAT4(DirectX::Colors::Gold);
//	}
//
//	for (size_t i = 0; i < grid.Vertices.size(); ++i, ++k)
//	{
//		vertices[k].Pos = grid.Vertices[i].Position;
//		//vertices[k].Color = XMFLOAT4(DirectX::Colors::ForestGreen);
//	}
//
//	for (size_t i = 0; i < sphere.Vertices.size(); ++i, ++k)
//	{
//		vertices[k].Pos = sphere.Vertices[i].Position;
//		//vertices[k].Color = XMFLOAT4(DirectX::Colors::Crimson);
//	}
//
//	/*for (size_t i = 0; i < sphere2.Vertices.size(); ++i, ++k)
//	{
//		vertices[k].Pos = sphere2.Vertices[i].Position;
//		vertices[k].Color = XMFLOAT4(DirectX::Colors::Crimson);
//	}*/
//
//	for (size_t i = 0; i < cylinder.Vertices.size(); ++i, ++k)
//	{
//		vertices[k].Pos = cylinder.Vertices[i].Position;
//		//vertices[k].Color = XMFLOAT4(DirectX::Colors::SteelBlue);
//	}
//
//	for (size_t i = 0; i < cone.Vertices.size(); ++i, ++k)
//	{
//		vertices[k].Pos = cone.Vertices[i].Position;
//		//vertices[k].Color = XMFLOAT4(DirectX::Colors::Red);
//	}
//
//
//	std::vector<std::uint16_t> indices;
//	indices.insert(indices.end(), std::begin(box.GetIndices16()), std::end(box.GetIndices16()));
//	indices.insert(indices.end(), std::begin(grid.GetIndices16()), std::end(grid.GetIndices16()));
//	indices.insert(indices.end(), std::begin(sphere.GetIndices16()), std::end(sphere.GetIndices16()));
//	//indices.insert(indices.end(), std::begin(sphere2.GetIndices16()), std::end(sphere2.GetIndices16()));
//	indices.insert(indices.end(), std::begin(cylinder.GetIndices16()), std::end(cylinder.GetIndices16()));
//	indices.insert(indices.end(), std::begin(cone.GetIndices16()), std::end(cone.GetIndices16()));
//
//	const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
//	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);
//
//	auto geo = std::make_unique<MeshGeometry>();
//	geo->Name = "shapeGeo";
//
//
//	ThrowIfFailed(D3DCreateBlob(vbByteSize, &geo->VertexBufferCPU));
//	CopyMemory(geo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);
//
//	ThrowIfFailed(D3DCreateBlob(ibByteSize, &geo->IndexBufferCPU));
//	CopyMemory(geo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);
//
//	geo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
//		mCommandList.Get(), vertices.data(), vbByteSize, geo->VertexBufferUploader);
//
//	geo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
//		mCommandList.Get(), indices.data(), ibByteSize, geo->IndexBufferUploader);
//
//	geo->VertexByteStride = sizeof(Vertex);
//	geo->VertexBufferByteSize = vbByteSize;
//	geo->IndexFormat = DXGI_FORMAT_R16_UINT;
//	geo->IndexBufferByteSize = ibByteSize;
//
//	geo->DrawArgs["box"] = boxSubmesh;
//	geo->DrawArgs["grid"] = gridSubmesh;
//	geo->DrawArgs["sphere"] = sphereSubmesh;
//	//geo->DrawArgs["sphere2"] = sphereSubmesh;
//	geo->DrawArgs["cylinder"] = cylinderSubmesh;
//	geo->DrawArgs["cone"] = coneSubmesh;
//
//	mGeometries[geo->Name] = std::move(geo);
//}
//
//void ShapesApp::BuildPSOs()
//{
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;
//
//	// PSO for opaque objects.
//
//	ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
//	opaquePsoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
//	opaquePsoDesc.pRootSignature = mRootSignature.Get();
//
//	opaquePsoDesc.VS =
//	{
//	 reinterpret_cast<BYTE*>(mShaders["standardVS"]->GetBufferPointer()),
//	 mShaders["standardVS"]->GetBufferSize()
//	};
//
//	opaquePsoDesc.PS =
//	{
//	 reinterpret_cast<BYTE*>(mShaders["opaquePS"]->GetBufferPointer()),
//	 mShaders["opaquePS"]->GetBufferSize()
//	};
//
//	opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
//	opaquePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
//	opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
//	opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
//	opaquePsoDesc.SampleMask = UINT_MAX;
//	opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//	opaquePsoDesc.NumRenderTargets = 1;
//	opaquePsoDesc.RTVFormats[0] = mBackBufferFormat;
//	opaquePsoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
//	opaquePsoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
//	opaquePsoDesc.DSVFormat = mDepthStencilFormat;
//
//	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&mPSOs["opaque"])));
//
//	// PSO for opaque wireframe objects.
//
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaqueWireframePsoDesc = opaquePsoDesc;
//	opaqueWireframePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
//	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaqueWireframePsoDesc, IID_PPV_ARGS(&mPSOs["opaque_wireframe"])));
//}
//
//
//
//void ShapesApp::BuildFrameResources()
//{
//	for (int i = 0; i < gNumFrameResources; ++i)
//	{
//		mFrameResources.push_back(std::make_unique<FrameResource>(md3dDevice.Get(),
//			1, (UINT)mAllRitems.size()));
//	}
//}
//
//
//
//void ShapesApp::BuildRenderItems()
//{
//	//Back Wall
//	auto boxRitem = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&boxRitem->World, XMMatrixScaling(10.0f, 20.0f, 100.0f) * XMMatrixTranslation(50.0f, 10.0f, -10.0f));
//
//	boxRitem->ObjCBIndex = 0;
//	boxRitem->Geo = mGeometries["shapeGeo"].get();
//	boxRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	boxRitem->IndexCount = boxRitem->Geo->DrawArgs["box"].IndexCount;
//	boxRitem->StartIndexLocation = boxRitem->Geo->DrawArgs["box"].StartIndexLocation;
//	boxRitem->BaseVertexLocation = boxRitem->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(boxRitem));
//
//	//Right wall
//	auto box2Ritem = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&box2Ritem->World, XMMatrixScaling(100.0f, 20.0f, 10.0f) * XMMatrixTranslation(5.0f, 10.0f, -55.0f));
//
//	box2Ritem->ObjCBIndex = 1;
//	box2Ritem->Geo = mGeometries["shapeGeo"].get();
//	box2Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	box2Ritem->IndexCount = box2Ritem->Geo->DrawArgs["box"].IndexCount;
//	box2Ritem->StartIndexLocation = box2Ritem->Geo->DrawArgs["box"].StartIndexLocation;
//	box2Ritem->BaseVertexLocation = box2Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(box2Ritem));
//
//	//Left Wall
//	auto box3Ritem = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&box3Ritem->World, XMMatrixScaling(100.0f, 20.0f, 10.0f) * XMMatrixTranslation(0.0f, 10.0f, 45.0f));
//
//	box3Ritem->ObjCBIndex = 2;
//	box3Ritem->Geo = mGeometries["shapeGeo"].get();
//	box3Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	box3Ritem->IndexCount = box3Ritem->Geo->DrawArgs["box"].IndexCount;
//	box3Ritem->StartIndexLocation = box3Ritem->Geo->DrawArgs["box"].StartIndexLocation;
//	box3Ritem->BaseVertexLocation = box3Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(box3Ritem));
//
//
//
//	//Front Wall1
//	auto box4Ritem = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&box4Ritem->World, XMMatrixScaling(10.0f, 20.0f, 35.0f) * XMMatrixTranslation(-45.0f, 10.0f, -37.0f));
//
//	box4Ritem->ObjCBIndex = 3;
//	box4Ritem->Geo = mGeometries["shapeGeo"].get();
//	box4Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	box4Ritem->IndexCount = box4Ritem->Geo->DrawArgs["box"].IndexCount;
//	box4Ritem->StartIndexLocation = box4Ritem->Geo->DrawArgs["box"].StartIndexLocation;
//	box4Ritem->BaseVertexLocation = box4Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(box4Ritem));
//
//	//Front Wall2
//	auto box5Ritem = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&box5Ritem->World, XMMatrixScaling(10.0f, 20.0f, 35.0f) * XMMatrixTranslation(-45.0f, 10.0f, 28.0f));
//
//	box5Ritem->ObjCBIndex = 4;
//	box5Ritem->Geo = mGeometries["shapeGeo"].get();
//	box5Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	box5Ritem->IndexCount = box5Ritem->Geo->DrawArgs["box"].IndexCount;
//	box5Ritem->StartIndexLocation = box5Ritem->Geo->DrawArgs["box"].StartIndexLocation;
//	box5Ritem->BaseVertexLocation = box5Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(box5Ritem));
//
//	//Front Wall3
//	auto box6Ritem = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&box6Ritem->World, XMMatrixScaling(10.0f, 6.0f, 31.0f) * XMMatrixTranslation(-45.0f, 17.0f, -4.0f));
//
//	box6Ritem->ObjCBIndex = 5;
//	box6Ritem->Geo = mGeometries["shapeGeo"].get();
//	box6Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	box6Ritem->IndexCount = box6Ritem->Geo->DrawArgs["box"].IndexCount;
//	box6Ritem->StartIndexLocation = box6Ritem->Geo->DrawArgs["box"].StartIndexLocation;
//	box6Ritem->BaseVertexLocation = box6Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(box6Ritem));
//
//	//Front Merlins
//	auto FMerlin1 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FMerlin1->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-40.0f, 22.0f, -25.0f));
//
//	FMerlin1->ObjCBIndex = 6;
//	FMerlin1->Geo = mGeometries["shapeGeo"].get();
//	FMerlin1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FMerlin1->IndexCount = FMerlin1->Geo->DrawArgs["box"].IndexCount;
//	FMerlin1->StartIndexLocation = FMerlin1->Geo->DrawArgs["box"].StartIndexLocation;
//	FMerlin1->BaseVertexLocation = FMerlin1->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FMerlin1));
//
//	auto FMerlin2 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FMerlin2->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-40.0f, 22.0f, -5.0f));
//
//	FMerlin2->ObjCBIndex = 7;
//	FMerlin2->Geo = mGeometries["shapeGeo"].get();
//	FMerlin2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FMerlin2->IndexCount = FMerlin2->Geo->DrawArgs["box"].IndexCount;
//	FMerlin2->StartIndexLocation = FMerlin2->Geo->DrawArgs["box"].StartIndexLocation;
//	FMerlin2->BaseVertexLocation = FMerlin2->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FMerlin2));
//
//	auto FMerlin3 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FMerlin3->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-40.0f, 22.0f, 15.0f));
//
//	FMerlin3->ObjCBIndex = 8;
//	FMerlin3->Geo = mGeometries["shapeGeo"].get();
//	FMerlin3->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FMerlin3->IndexCount = FMerlin3->Geo->DrawArgs["box"].IndexCount;
//	FMerlin3->StartIndexLocation = FMerlin3->Geo->DrawArgs["box"].StartIndexLocation;
//	FMerlin3->BaseVertexLocation = FMerlin3->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FMerlin3));
//
//	auto FMerlin4 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FMerlin4->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, 23.0f));
//
//	FMerlin4->ObjCBIndex = 9;
//	FMerlin4->Geo = mGeometries["shapeGeo"].get();
//	FMerlin4->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FMerlin4->IndexCount = FMerlin4->Geo->DrawArgs["box"].IndexCount;
//	FMerlin4->StartIndexLocation = FMerlin4->Geo->DrawArgs["box"].StartIndexLocation;
//	FMerlin4->BaseVertexLocation = FMerlin4->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FMerlin4));
//
//	auto FMerlin5 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FMerlin5->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, 3.0f));
//
//	FMerlin5->ObjCBIndex = 10;
//	FMerlin5->Geo = mGeometries["shapeGeo"].get();
//	FMerlin5->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FMerlin5->IndexCount = FMerlin5->Geo->DrawArgs["box"].IndexCount;
//	FMerlin5->StartIndexLocation = FMerlin5->Geo->DrawArgs["box"].StartIndexLocation;
//	FMerlin5->BaseVertexLocation = FMerlin5->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FMerlin5));
//
//	auto FMerlin6 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FMerlin6->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, -17.0f));
//
//	FMerlin6->ObjCBIndex = 11;
//	FMerlin6->Geo = mGeometries["shapeGeo"].get();
//	FMerlin6->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FMerlin6->IndexCount = FMerlin6->Geo->DrawArgs["box"].IndexCount;
//	FMerlin6->StartIndexLocation = FMerlin6->Geo->DrawArgs["box"].StartIndexLocation;
//	FMerlin6->BaseVertexLocation = FMerlin6->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FMerlin6));
//
//	auto FMerlin7 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FMerlin7->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, -37.0f));
//
//	FMerlin7->ObjCBIndex = 12;
//	FMerlin7->Geo = mGeometries["shapeGeo"].get();
//	FMerlin7->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FMerlin7->IndexCount = FMerlin7->Geo->DrawArgs["box"].IndexCount;
//	FMerlin7->StartIndexLocation = FMerlin7->Geo->DrawArgs["box"].StartIndexLocation;
//	FMerlin7->BaseVertexLocation = FMerlin7->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FMerlin7));
//
//	//Front Crenel
//	auto FCrenel1 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FCrenel1->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(-50.2f, 20.0f, -4.0f));
//
//	FCrenel1->ObjCBIndex = 13;
//	FCrenel1->Geo = mGeometries["shapeGeo"].get();
//	FCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FCrenel1->IndexCount = FCrenel1->Geo->DrawArgs["box"].IndexCount;
//	FCrenel1->StartIndexLocation = FCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
//	FCrenel1->BaseVertexLocation = FCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FCrenel1));
//
//	auto FCrenel2 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&FCrenel2->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(-40.2f, 20.0f, -4.0f));
//
//	FCrenel2->ObjCBIndex = 14;
//	FCrenel2->Geo = mGeometries["shapeGeo"].get();
//	FCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	FCrenel2->IndexCount = FCrenel2->Geo->DrawArgs["box"].IndexCount;
//	FCrenel2->StartIndexLocation = FCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
//	FCrenel2->BaseVertexLocation = FCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(FCrenel2));
//
//	//Back Merlins
//	auto BMerlin1 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BMerlin1->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(45.0f, 22.0f, -25.0f));
//
//	BMerlin1->ObjCBIndex = 15;
//	BMerlin1->Geo = mGeometries["shapeGeo"].get();
//	BMerlin1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BMerlin1->IndexCount = BMerlin1->Geo->DrawArgs["box"].IndexCount;
//	BMerlin1->StartIndexLocation = BMerlin1->Geo->DrawArgs["box"].StartIndexLocation;
//	BMerlin1->BaseVertexLocation = BMerlin1->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BMerlin1));
//
//	auto BMerlin2 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BMerlin2->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(45.0f, 22.0f, -5.0f));
//
//	BMerlin2->ObjCBIndex = 16;
//	BMerlin2->Geo = mGeometries["shapeGeo"].get();
//	BMerlin2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BMerlin2->IndexCount = BMerlin2->Geo->DrawArgs["box"].IndexCount;
//	BMerlin2->StartIndexLocation = BMerlin2->Geo->DrawArgs["box"].StartIndexLocation;
//	BMerlin2->BaseVertexLocation = BMerlin2->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BMerlin2));
//
//	auto BMerlin3 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BMerlin3->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(45.0f, 22.0f, 15.0f));
//
//	BMerlin3->ObjCBIndex = 17;
//	BMerlin3->Geo = mGeometries["shapeGeo"].get();
//	BMerlin3->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BMerlin3->IndexCount = BMerlin3->Geo->DrawArgs["box"].IndexCount;
//	BMerlin3->StartIndexLocation = BMerlin3->Geo->DrawArgs["box"].StartIndexLocation;
//	BMerlin3->BaseVertexLocation = BMerlin3->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BMerlin3));
//
//	auto BMerlin4 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BMerlin4->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, 23.0f));
//
//	BMerlin4->ObjCBIndex = 18;
//	BMerlin4->Geo = mGeometries["shapeGeo"].get();
//	BMerlin4->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BMerlin4->IndexCount = BMerlin4->Geo->DrawArgs["box"].IndexCount;
//	BMerlin4->StartIndexLocation = BMerlin4->Geo->DrawArgs["box"].StartIndexLocation;
//	BMerlin4->BaseVertexLocation = BMerlin4->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BMerlin4));
//
//	auto BMerlin5 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BMerlin5->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, 3.0f));
//
//	BMerlin5->ObjCBIndex = 19;
//	BMerlin5->Geo = mGeometries["shapeGeo"].get();
//	BMerlin5->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BMerlin5->IndexCount = BMerlin5->Geo->DrawArgs["box"].IndexCount;
//	BMerlin5->StartIndexLocation = BMerlin5->Geo->DrawArgs["box"].StartIndexLocation;
//	BMerlin5->BaseVertexLocation = BMerlin5->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BMerlin5));
//
//	auto BMerlin6 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BMerlin6->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, -17.0f));
//
//	BMerlin6->ObjCBIndex = 20;
//	BMerlin6->Geo = mGeometries["shapeGeo"].get();
//	BMerlin6->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BMerlin6->IndexCount = BMerlin6->Geo->DrawArgs["box"].IndexCount;
//	BMerlin6->StartIndexLocation = BMerlin6->Geo->DrawArgs["box"].StartIndexLocation;
//	BMerlin6->BaseVertexLocation = BMerlin6->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BMerlin6));
//
//	auto BMerlin7 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BMerlin7->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, -37.0f));
//
//	BMerlin7->ObjCBIndex = 21;
//	BMerlin7->Geo = mGeometries["shapeGeo"].get();
//	BMerlin7->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BMerlin7->IndexCount = BMerlin7->Geo->DrawArgs["box"].IndexCount;
//	BMerlin7->StartIndexLocation = BMerlin7->Geo->DrawArgs["box"].StartIndexLocation;
//	BMerlin7->BaseVertexLocation = BMerlin7->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BMerlin7));
//
//	//Back Crenel
//	auto BCrenel1 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BCrenel1->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(55.2f, 20.0f, -4.0f));
//
//	BCrenel1->ObjCBIndex = 22;
//	BCrenel1->Geo = mGeometries["shapeGeo"].get();
//	BCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BCrenel1->IndexCount = BCrenel1->Geo->DrawArgs["box"].IndexCount;
//	BCrenel1->StartIndexLocation = BCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
//	BCrenel1->BaseVertexLocation = BCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BCrenel1));
//	//
//	auto BCrenel2 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&BCrenel2->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(45.2f, 20.0f, -4.0f));
//
//	BCrenel2->ObjCBIndex = 23;
//	BCrenel2->Geo = mGeometries["shapeGeo"].get();
//	BCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	BCrenel2->IndexCount = BCrenel2->Geo->DrawArgs["box"].IndexCount;
//	BCrenel2->StartIndexLocation = BCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
//	BCrenel2->BaseVertexLocation = BCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(BCrenel2));
//	//
//
//	auto gridRitem = std::make_unique<RenderItem>();
//
//	gridRitem->World = MathHelper::Identity4x4();
//	gridRitem->ObjCBIndex = 24;
//	gridRitem->Geo = mGeometries["shapeGeo"].get();
//	gridRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//
//	gridRitem->IndexCount = gridRitem->Geo->DrawArgs["grid"].IndexCount;
//	gridRitem->StartIndexLocation = gridRitem->Geo->DrawArgs["grid"].StartIndexLocation;
//	gridRitem->BaseVertexLocation = gridRitem->Geo->DrawArgs["grid"].BaseVertexLocation;
//
//	mAllRitems.push_back(std::move(gridRitem));
//
//	//Left crenal
//
//	auto LCrenel1 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&LCrenel1->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(1.0f, 20.0f, 40.0f));
//
//	LCrenel1->ObjCBIndex = 25;
//	LCrenel1->Geo = mGeometries["shapeGeo"].get();
//	LCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	LCrenel1->IndexCount = LCrenel1->Geo->DrawArgs["box"].IndexCount;
//	LCrenel1->StartIndexLocation = LCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
//	LCrenel1->BaseVertexLocation = LCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(LCrenel1));
//
//	auto LCrenel2 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&LCrenel2->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(1.0f, 20.0f, 50.0f));
//
//	LCrenel2->ObjCBIndex = 26;
//	LCrenel2->Geo = mGeometries["shapeGeo"].get();
//	LCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	LCrenel2->IndexCount = LCrenel2->Geo->DrawArgs["box"].IndexCount;
//	LCrenel2->StartIndexLocation = LCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
//	LCrenel2->BaseVertexLocation = LCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(LCrenel2));
//
//
//	//Right crenel
//	auto RCrenel1 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&RCrenel1->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(5.0f, 20.0f, -50.0f));
//
//	RCrenel1->ObjCBIndex = 27;
//	RCrenel1->Geo = mGeometries["shapeGeo"].get();
//	RCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	RCrenel1->IndexCount = RCrenel1->Geo->DrawArgs["box"].IndexCount;
//	RCrenel1->StartIndexLocation = RCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
//	RCrenel1->BaseVertexLocation = RCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(RCrenel1));
//
//	auto RCrenel2 = std::make_unique<RenderItem>();
//
//	XMStoreFloat4x4(&RCrenel2->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(5.0f, 20.0f, -60.0f));
//
//	RCrenel2->ObjCBIndex = 28;
//	RCrenel2->Geo = mGeometries["shapeGeo"].get();
//	RCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	RCrenel2->IndexCount = RCrenel2->Geo->DrawArgs["box"].IndexCount;
//	RCrenel2->StartIndexLocation = RCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
//	RCrenel2->BaseVertexLocation = RCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
//	mAllRitems.push_back(std::move(RCrenel2));
//
//
//
//	UINT objCBIndex = 29;
//
//
//
//	for (int i = 0; i < 2; ++i)
//	{
//		auto leftCylRitem = std::make_unique<RenderItem>();
//		auto rightCylRitem = std::make_unique<RenderItem>();
//
//		auto leftConeRitem = std::make_unique<RenderItem>();
//		auto rightConeRitem = std::make_unique<RenderItem>();
//
//		auto leftSphereRitem = std::make_unique<RenderItem>();
//		auto rightSphereRitem = std::make_unique<RenderItem>();
//
//		XMMATRIX leftSphereWorld = XMMatrixTranslation(-45.0f, 30.0f, -53.0f + i * 97.0f);
//		XMMATRIX rightSphereWorld = XMMatrixTranslation(+50.0f, 30.0f, -53.0f + i * 97.0f);
//
//		XMMATRIX leftCylWorld = XMMatrixTranslation(-45.0f, 15.0f, -53.0f + i * 97.0f);
//		XMMATRIX rightCylWorld = XMMatrixTranslation(+50.0f, 15.0f, -53.0f + i * 97.0f);
//
//		XMMATRIX leftConeWorld = XMMatrixTranslation(-45.0f, 15.0f, -53.0f + i * 97.0f);
//		XMMATRIX rightConeWorld = XMMatrixTranslation(+50.0f, 15.0f, -53.0f + i * 97.0f);
//
//		XMStoreFloat4x4(&leftCylRitem->World, rightCylWorld);
//
//		leftCylRitem->ObjCBIndex = objCBIndex++;
//
//		leftCylRitem->Geo = mGeometries["shapeGeo"].get();
//		leftCylRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//		leftCylRitem->IndexCount = leftCylRitem->Geo->DrawArgs["cylinder"].IndexCount;
//		leftCylRitem->StartIndexLocation = leftCylRitem->Geo->DrawArgs["cylinder"].StartIndexLocation;
//		leftCylRitem->BaseVertexLocation = leftCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;
//
//		XMStoreFloat4x4(&rightCylRitem->World, leftCylWorld);
//
//		rightCylRitem->ObjCBIndex = objCBIndex++;
//
//		rightCylRitem->Geo = mGeometries["shapeGeo"].get();
//		rightCylRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//		rightCylRitem->IndexCount = rightCylRitem->Geo->DrawArgs["cylinder"].IndexCount;
//		rightCylRitem->StartIndexLocation = rightCylRitem->Geo->DrawArgs["cylinder"].StartIndexLocation;
//		rightCylRitem->BaseVertexLocation = rightCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;
//
//		XMStoreFloat4x4(&leftConeRitem->World, rightConeWorld);
//
//		leftConeRitem->ObjCBIndex = objCBIndex++;
//		leftConeRitem->Geo = mGeometries["shapeGeo"].get();
//		leftConeRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//		leftConeRitem->IndexCount = leftConeRitem->Geo->DrawArgs["cone"].IndexCount;
//		leftConeRitem->StartIndexLocation = leftConeRitem->Geo->DrawArgs["cone"].StartIndexLocation;
//		leftConeRitem->BaseVertexLocation = leftConeRitem->Geo->DrawArgs["cone"].BaseVertexLocation;
//
//		XMStoreFloat4x4(&rightConeRitem->World, leftCylWorld);
//
//		rightConeRitem->ObjCBIndex = objCBIndex++;
//
//		rightConeRitem->Geo = mGeometries["shapeGeo"].get();
//		rightConeRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//		rightConeRitem->IndexCount = rightConeRitem->Geo->DrawArgs["cone"].IndexCount;
//		rightConeRitem->StartIndexLocation = rightConeRitem->Geo->DrawArgs["cone"].StartIndexLocation;
//		rightConeRitem->BaseVertexLocation = rightConeRitem->Geo->DrawArgs["cone"].BaseVertexLocation;
//
//		XMStoreFloat4x4(&leftSphereRitem->World, leftSphereWorld);
//
//		leftSphereRitem->ObjCBIndex = objCBIndex++;
//		leftSphereRitem->Geo = mGeometries["shapeGeo"].get();
//		leftSphereRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//		leftSphereRitem->IndexCount = leftSphereRitem->Geo->DrawArgs["sphere"].IndexCount;
//		leftSphereRitem->StartIndexLocation = leftSphereRitem->Geo->DrawArgs["sphere"].StartIndexLocation;
//		leftSphereRitem->BaseVertexLocation = leftSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;
//
//		XMStoreFloat4x4(&rightSphereRitem->World, rightSphereWorld);
//
//		rightSphereRitem->ObjCBIndex = objCBIndex++;
//
//		rightSphereRitem->Geo = mGeometries["shapeGeo"].get();
//		rightSphereRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//		rightSphereRitem->IndexCount = rightSphereRitem->Geo->DrawArgs["sphere"].IndexCount;
//		rightSphereRitem->StartIndexLocation = rightSphereRitem->Geo->DrawArgs["sphere"].StartIndexLocation;
//		rightSphereRitem->BaseVertexLocation = rightSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;
//
//		mAllRitems.push_back(std::move(leftCylRitem));
//		mAllRitems.push_back(std::move(rightCylRitem));
//		mAllRitems.push_back(std::move(leftConeRitem));
//		mAllRitems.push_back(std::move(rightConeRitem));
//		mAllRitems.push_back(std::move(leftSphereRitem));
//		mAllRitems.push_back(std::move(rightSphereRitem));
//	}
//
//
//
//
//
//	// All the render items are opaque.
//	for (auto& e : mAllRitems)
//		mOpaqueRitems.push_back(e.get());
//}
//
//void ShapesApp::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems)
//{
//	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
//	auto objectCB = mCurrFrameResource->ObjectCB->Resource();
//	// For each render item...
//
//	for (size_t i = 0; i < ritems.size(); ++i)
//	{
//		auto ri = ritems[i];
//		cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
//		cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
//		cmdList->IASetPrimitiveTopology(ri->PrimitiveType);
//
//		// Offset to the CBV in the descriptor heap for this object and for this frame resource.
//
//		UINT cbvIndex = mCurrFrameResourceIndex * (UINT)mOpaqueRitems.size() + ri->ObjCBIndex;
//
//		auto cbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
//
//		cbvHandle.Offset(cbvIndex, mCbvSrvUavDescriptorSize);
//
//		cmdList->SetGraphicsRootDescriptorTable(0, cbvHandle);
//		cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
//	}
//}

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")

const int gNumFrameResources = 3;

// Lightweight structure stores parameters to draw a shape.  This will
// vary from app-to-app.
struct RenderItem
{
	RenderItem() = default;
	RenderItem(const RenderItem& rhs) = delete;

	// World matrix of the shape that describes the object's local space
	// relative to the world space, which defines the position, orientation,
	// and scale of the object in the world.
	XMFLOAT4X4 World = MathHelper::Identity4x4();

	XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

	// Dirty flag indicating the object data has changed and we need to update the constant buffer.
	// Because we have an object cbuffer for each FrameResource, we have to apply the
	// update to each FrameResource.  Thus, when we modify obect data we should set 
	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
	int NumFramesDirty = gNumFrameResources;

	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
	UINT ObjCBIndex = -1;

	Material* Mat = nullptr;
	MeshGeometry* Geo = nullptr;

	// Primitive topology.
	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// DrawIndexedInstanced parameters.
	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	int BaseVertexLocation = 0;
};

class TexColumnsApp : public D3DApp
{
public:
	TexColumnsApp(HINSTANCE hInstance);
	TexColumnsApp(const TexColumnsApp& rhs) = delete;
	TexColumnsApp& operator=(const TexColumnsApp& rhs) = delete;
	~TexColumnsApp();

	virtual bool Initialize()override;

private:
	virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;

	void OnKeyboardInput(const GameTimer& gt);
	void UpdateCamera(const GameTimer& gt);
	void AnimateMaterials(const GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMaterialCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);

	void LoadTextures();
	void BuildRootSignature();
	void BuildDescriptorHeaps();
	void BuildShadersAndInputLayout();
	void BuildShapeGeometry();
	void BuildPSOs();
	void BuildFrameResources();
	void BuildMaterials();
	void BuildRenderItems();
	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

private:

	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
	FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;

	UINT mCbvSrvDescriptorSize = 0;

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	// Render items divided by PSO.
	std::vector<RenderItem*> mOpaqueRitems;

	PassConstants mMainPassCB;

	XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float mTheta = 1.5f * XM_PI;
	float mPhi = 0.2f * XM_PI;
	float mRadius = 100.0f;

	POINT mLastMousePos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		TexColumnsApp theApp(hInstance);
		if (!theApp.Initialize())
			return 0;

		return theApp.Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}

TexColumnsApp::TexColumnsApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
}

TexColumnsApp::~TexColumnsApp()
{
	if (md3dDevice != nullptr)
		FlushCommandQueue();
}

bool TexColumnsApp::Initialize()
{
	if (!D3DApp::Initialize())
		return false;

	// Reset the command list to prep for initialization commands.
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	// Get the increment size of a descriptor in this heap type.  This is hardware specific, 
	// so we have to query this information.
	mCbvSrvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);


	LoadTextures();
	BuildRootSignature();
	BuildDescriptorHeaps();
	BuildShadersAndInputLayout();
	BuildShapeGeometry();
	BuildMaterials();
	BuildRenderItems();
	BuildFrameResources();
	BuildPSOs();

	// Execute the initialization commands.
	ThrowIfFailed(mCommandList->Close());
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	FlushCommandQueue();

	return true;
}

void TexColumnsApp::OnResize()
{
	D3DApp::OnResize();

	// The window resized, so update the aspect ratio and recompute the projection matrix.
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}

void TexColumnsApp::Update(const GameTimer& gt)
{
	OnKeyboardInput(gt);
	UpdateCamera(gt);

	// Cycle through the circular frame resource array.
	mCurrFrameResourceIndex = (mCurrFrameResourceIndex + 1) % gNumFrameResources;
	mCurrFrameResource = mFrameResources[mCurrFrameResourceIndex].get();

	// Has the GPU finished processing the commands of the current frame resource?
	// If not, wait until the GPU has completed commands up to this fence point.
	if (mCurrFrameResource->Fence != 0 && mFence->GetCompletedValue() < mCurrFrameResource->Fence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);
		ThrowIfFailed(mFence->SetEventOnCompletion(mCurrFrameResource->Fence, eventHandle));
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}

	AnimateMaterials(gt);
	UpdateObjectCBs(gt);
	UpdateMaterialCBs(gt);
	UpdateMainPassCB(gt);
}

void TexColumnsApp::Draw(const GameTimer& gt)
{
	auto cmdListAlloc = mCurrFrameResource->CmdListAlloc;

	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(cmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(), mPSOs["opaque"].Get()));

	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	// Indicate a state transition on the resource usage.
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	// Clear the back buffer and depth buffer.
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

	ID3D12DescriptorHeap* descriptorHeaps[] = { mSrvDescriptorHeap.Get() };
	mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	mCommandList->SetGraphicsRootSignature(mRootSignature.Get());

	auto passCB = mCurrFrameResource->PassCB->Resource();
	mCommandList->SetGraphicsRootConstantBufferView(2, passCB->GetGPUVirtualAddress());

	DrawRenderItems(mCommandList.Get(), mOpaqueRitems);

	// Indicate a state transition on the resource usage.
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	// Done recording commands.
	ThrowIfFailed(mCommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Swap the back and front buffers
	ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	// Advance the fence value to mark commands up to this fence point.
	mCurrFrameResource->Fence = ++mCurrentFence;

	// Add an instruction to the command queue to set a new fence point. 
	// Because we are on the GPU timeline, the new fence point won't be 
	// set until the GPU finishes processing all the commands prior to this Signal().
	mCommandQueue->Signal(mFence.Get(), mCurrentFence);
}

void TexColumnsApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void TexColumnsApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void TexColumnsApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi += dy;

		// Restrict the angle mPhi.
		mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.2 unit in the scene.
		float dx = 0.05f * static_cast<float>(x - mLastMousePos.x);
		float dy = 0.05f * static_cast<float>(y - mLastMousePos.y);

		// Update the camera radius based on input.
		mRadius += dx - dy;

		// Restrict the radius.
		mRadius = MathHelper::Clamp(mRadius, 5.0f, 150.0f);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void TexColumnsApp::OnKeyboardInput(const GameTimer& gt)
{
}

void TexColumnsApp::UpdateCamera(const GameTimer& gt)
{
	// Convert Spherical to Cartesian coordinates.
	mEyePos.x = mRadius * sinf(mPhi) * cosf(mTheta);
	mEyePos.z = mRadius * sinf(mPhi) * sinf(mTheta);
	mEyePos.y = mRadius * cosf(mPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(mEyePos.x, mEyePos.y, mEyePos.z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&mView, view);
}

void TexColumnsApp::AnimateMaterials(const GameTimer& gt)
{

}

void TexColumnsApp::UpdateObjectCBs(const GameTimer& gt)
{
	auto currObjectCB = mCurrFrameResource->ObjectCB.get();
	for (auto& e : mAllRitems)
	{
		// Only update the cbuffer data if the constants have changed.  
		// This needs to be tracked per frame resource.
		if (e->NumFramesDirty > 0)
		{
			XMMATRIX world = XMLoadFloat4x4(&e->World);
			XMMATRIX texTransform = XMLoadFloat4x4(&e->TexTransform);

			ObjectConstants objConstants;
			XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
			XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));

			currObjectCB->CopyData(e->ObjCBIndex, objConstants);

			// Next FrameResource need to be updated too.
			e->NumFramesDirty--;
		}
	}
}

void TexColumnsApp::UpdateMaterialCBs(const GameTimer& gt)
{
	auto currMaterialCB = mCurrFrameResource->MaterialCB.get();
	for (auto& e : mMaterials)
	{
		// Only update the cbuffer data if the constants have changed.  If the cbuffer
		// data changes, it needs to be updated for each FrameResource.
		Material* mat = e.second.get();
		if (mat->NumFramesDirty > 0)
		{
			XMMATRIX matTransform = XMLoadFloat4x4(&mat->MatTransform);

			MaterialConstants matConstants;
			matConstants.DiffuseAlbedo = mat->DiffuseAlbedo;
			matConstants.FresnelR0 = mat->FresnelR0;
			matConstants.Roughness = mat->Roughness;
			XMStoreFloat4x4(&matConstants.MatTransform, XMMatrixTranspose(matTransform));

			currMaterialCB->CopyData(mat->MatCBIndex, matConstants);

			// Next FrameResource need to be updated too.
			mat->NumFramesDirty--;
		}
	}
}

void TexColumnsApp::UpdateMainPassCB(const GameTimer& gt)
{
	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);

	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
	XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
	XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);

	XMStoreFloat4x4(&mMainPassCB.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&mMainPassCB.InvView, XMMatrixTranspose(invView));
	XMStoreFloat4x4(&mMainPassCB.Proj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&mMainPassCB.InvProj, XMMatrixTranspose(invProj));
	XMStoreFloat4x4(&mMainPassCB.ViewProj, XMMatrixTranspose(viewProj));
	XMStoreFloat4x4(&mMainPassCB.InvViewProj, XMMatrixTranspose(invViewProj));
	mMainPassCB.EyePosW = mEyePos;
	mMainPassCB.RenderTargetSize = XMFLOAT2((float)mClientWidth, (float)mClientHeight);
	mMainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / mClientWidth, 1.0f / mClientHeight);
	mMainPassCB.NearZ = 1.0f;
	mMainPassCB.FarZ = 1000.0f;
	mMainPassCB.TotalTime = gt.TotalTime();
	mMainPassCB.DeltaTime = gt.DeltaTime();
	mMainPassCB.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };

	// Directional lights
	mMainPassCB.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[0].Strength = { 0.8f, 0.8f, 0.8f };
	mMainPassCB.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[1].Strength = { 0.4f, 0.4f, 0.4f };
	mMainPassCB.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
	mMainPassCB.Lights[2].Strength = { 0.2f, 0.2f, 0.2f };

	// Poijnt lights
	mMainPassCB.Lights[3].Position = { 0.0f, 5.0f, -3.0f };
	mMainPassCB.Lights[3].Strength = { 0.95f, 0.95f, 0.95f };

	auto currPassCB = mCurrFrameResource->PassCB.get();
	currPassCB->CopyData(0, mMainPassCB);
}

void TexColumnsApp::LoadTextures()
{
	auto bricksTex = std::make_unique<Texture>();
	bricksTex->Name = "bricksTex";
	bricksTex->Filename = L"Textures/brick.dds";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(md3dDevice.Get(),
		mCommandList.Get(), bricksTex->Filename.c_str(),
		bricksTex->Resource, bricksTex->UploadHeap));

	auto stoneTex = std::make_unique<Texture>();
	stoneTex->Name = "stoneTex";
	stoneTex->Filename = L"Textures/Marble.dds";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(md3dDevice.Get(),
		mCommandList.Get(), stoneTex->Filename.c_str(),
		stoneTex->Resource, stoneTex->UploadHeap));

	auto brickcleanTex = std::make_unique<Texture>();
	brickcleanTex->Name = "tileTex";
	brickcleanTex->Filename = L"Textures/brickC.dds";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(md3dDevice.Get(),
		mCommandList.Get(), brickcleanTex->Filename.c_str(),
		brickcleanTex->Resource, brickcleanTex->UploadHeap));

	mTextures[bricksTex->Name] = std::move(bricksTex);
	mTextures[stoneTex->Name] = std::move(stoneTex);
	mTextures[brickcleanTex->Name] = std::move(brickcleanTex);
}

void TexColumnsApp::BuildRootSignature()
{
	CD3DX12_DESCRIPTOR_RANGE texTable;
	texTable.Init(
		D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
		1,  // number of descriptors
		0); // register t0

	// Root parameter can be a table, root descriptor or root constants.
	CD3DX12_ROOT_PARAMETER slotRootParameter[4];

	// Perfomance TIP: Order from most frequent to least frequent.
	slotRootParameter[0].InitAsDescriptorTable(1, &texTable, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[1].InitAsConstantBufferView(0); // register b0
	slotRootParameter[2].InitAsConstantBufferView(1); // register b1
	slotRootParameter[3].InitAsConstantBufferView(2); // register b2

	auto staticSamplers = GetStaticSamplers();

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(4, slotRootParameter,
		(UINT)staticSamplers.size(), staticSamplers.data(),
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(mRootSignature.GetAddressOf())));
}

void TexColumnsApp::BuildDescriptorHeaps()
{
	//
	// Create the SRV heap.
	//
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 3;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&mSrvDescriptorHeap)));

	//
	// Fill out the heap with actual descriptors.
	//
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	auto bricksTex = mTextures["bricksTex"]->Resource;
	auto stoneTex = mTextures["stoneTex"]->Resource;
	auto tileTex = mTextures["tileTex"]->Resource;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = bricksTex->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = bricksTex->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	md3dDevice->CreateShaderResourceView(bricksTex.Get(), &srvDesc, hDescriptor);

	// next descriptor
	hDescriptor.Offset(1, mCbvSrvDescriptorSize);

	srvDesc.Format = stoneTex->GetDesc().Format;
	srvDesc.Texture2D.MipLevels = stoneTex->GetDesc().MipLevels;
	md3dDevice->CreateShaderResourceView(stoneTex.Get(), &srvDesc, hDescriptor);

	// next descriptor
	hDescriptor.Offset(1, mCbvSrvDescriptorSize);

	srvDesc.Format = tileTex->GetDesc().Format;
	srvDesc.Texture2D.MipLevels = tileTex->GetDesc().MipLevels;
	md3dDevice->CreateShaderResourceView(tileTex.Get(), &srvDesc, hDescriptor);
}

void TexColumnsApp::BuildShadersAndInputLayout()
{
	const D3D_SHADER_MACRO alphaTestDefines[] =
	{
		"ALPHA_TEST", "1",
		NULL, NULL
	};

	mShaders["standardVS"] = d3dUtil::CompileShader(L"Shaders\\Default.hlsl", nullptr, "VS", "vs_5_0");
	mShaders["opaquePS"] = d3dUtil::CompileShader(L"Shaders\\Default.hlsl", nullptr, "PS", "ps_5_0");

	mInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
}

void TexColumnsApp::BuildShapeGeometry()
{
	GeometryGenerator geoGen;
	GeometryGenerator::MeshData box = geoGen.CreateBox(1.0f, 1.0f, 1.0f, 3);
	GeometryGenerator::MeshData grid = geoGen.CreateGrid(100.0f, 100.0f, 60, 40);
	GeometryGenerator::MeshData sphere = geoGen.CreateSphere(12.0f, 20, 20);
	GeometryGenerator::MeshData cylinder = geoGen.CreateCylinder(10.0f, 10.0f, 30.0f, 20, 20);

	//
	// We are concatenating all the geometry into one big vertex/index buffer.  So
	// define the regions in the buffer each submesh covers.
	//

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	UINT boxVertexOffset = 0;
	UINT gridVertexOffset = (UINT)box.Vertices.size();
	UINT sphereVertexOffset = gridVertexOffset + (UINT)grid.Vertices.size();
	UINT cylinderVertexOffset = sphereVertexOffset + (UINT)sphere.Vertices.size();

	// Cache the starting index for each object in the concatenated index buffer.
	UINT boxIndexOffset = 0;
	UINT gridIndexOffset = (UINT)box.Indices32.size();
	UINT sphereIndexOffset = gridIndexOffset + (UINT)grid.Indices32.size();
	UINT cylinderIndexOffset = sphereIndexOffset + (UINT)sphere.Indices32.size();

	SubmeshGeometry boxSubmesh;
	boxSubmesh.IndexCount = (UINT)box.Indices32.size();
	boxSubmesh.StartIndexLocation = boxIndexOffset;
	boxSubmesh.BaseVertexLocation = boxVertexOffset;

	SubmeshGeometry gridSubmesh;
	gridSubmesh.IndexCount = (UINT)grid.Indices32.size();
	gridSubmesh.StartIndexLocation = gridIndexOffset;
	gridSubmesh.BaseVertexLocation = gridVertexOffset;

	SubmeshGeometry sphereSubmesh;
	sphereSubmesh.IndexCount = (UINT)sphere.Indices32.size();
	sphereSubmesh.StartIndexLocation = sphereIndexOffset;
	sphereSubmesh.BaseVertexLocation = sphereVertexOffset;

	SubmeshGeometry cylinderSubmesh;
	cylinderSubmesh.IndexCount = (UINT)cylinder.Indices32.size();
	cylinderSubmesh.StartIndexLocation = cylinderIndexOffset;
	cylinderSubmesh.BaseVertexLocation = cylinderVertexOffset;

	//
	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	//

	auto totalVertexCount =
		box.Vertices.size() +
		grid.Vertices.size() +
		sphere.Vertices.size() +
		cylinder.Vertices.size();

	std::vector<Vertex> vertices(totalVertexCount);

	UINT k = 0;
	for (size_t i = 0; i < box.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = box.Vertices[i].Position;
		vertices[k].Normal = box.Vertices[i].Normal;
		vertices[k].TexC = box.Vertices[i].TexC;
	}

	for (size_t i = 0; i < grid.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = grid.Vertices[i].Position;
		vertices[k].Normal = grid.Vertices[i].Normal;
		vertices[k].TexC = grid.Vertices[i].TexC;
	}

	for (size_t i = 0; i < sphere.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = sphere.Vertices[i].Position;
		vertices[k].Normal = sphere.Vertices[i].Normal;
		vertices[k].TexC = sphere.Vertices[i].TexC;
	}

	for (size_t i = 0; i < cylinder.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = cylinder.Vertices[i].Position;
		vertices[k].Normal = cylinder.Vertices[i].Normal;
		vertices[k].TexC = cylinder.Vertices[i].TexC;
	}

	std::vector<std::uint16_t> indices;
	indices.insert(indices.end(), std::begin(box.GetIndices16()), std::end(box.GetIndices16()));
	indices.insert(indices.end(), std::begin(grid.GetIndices16()), std::end(grid.GetIndices16()));
	indices.insert(indices.end(), std::begin(sphere.GetIndices16()), std::end(sphere.GetIndices16()));
	indices.insert(indices.end(), std::begin(cylinder.GetIndices16()), std::end(cylinder.GetIndices16()));

	const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

	auto geo = std::make_unique<MeshGeometry>();
	geo->Name = "shapeGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &geo->VertexBufferCPU));
	CopyMemory(geo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &geo->IndexBufferCPU));
	CopyMemory(geo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	geo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), vertices.data(), vbByteSize, geo->VertexBufferUploader);

	geo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), indices.data(), ibByteSize, geo->IndexBufferUploader);

	geo->VertexByteStride = sizeof(Vertex);
	geo->VertexBufferByteSize = vbByteSize;
	geo->IndexFormat = DXGI_FORMAT_R16_UINT;
	geo->IndexBufferByteSize = ibByteSize;

	geo->DrawArgs["box"] = boxSubmesh;
	geo->DrawArgs["grid"] = gridSubmesh;
	geo->DrawArgs["sphere"] = sphereSubmesh;
	geo->DrawArgs["cylinder"] = cylinderSubmesh;

	mGeometries[geo->Name] = std::move(geo);
}

void TexColumnsApp::BuildPSOs()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;

	//
	// PSO for opaque objects.
	//
	ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	opaquePsoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	opaquePsoDesc.pRootSignature = mRootSignature.Get();
	opaquePsoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mShaders["standardVS"]->GetBufferPointer()),
		mShaders["standardVS"]->GetBufferSize()
	};
	opaquePsoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mShaders["opaquePS"]->GetBufferPointer()),
		mShaders["opaquePS"]->GetBufferSize()
	};
	opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	opaquePsoDesc.SampleMask = UINT_MAX;
	opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	opaquePsoDesc.NumRenderTargets = 1;
	opaquePsoDesc.RTVFormats[0] = mBackBufferFormat;
	opaquePsoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	opaquePsoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	opaquePsoDesc.DSVFormat = mDepthStencilFormat;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&mPSOs["opaque"])));
}

void TexColumnsApp::BuildFrameResources()
{
	for (int i = 0; i < gNumFrameResources; ++i)
	{
		mFrameResources.push_back(std::make_unique<FrameResource>(md3dDevice.Get(),
			1, (UINT)mAllRitems.size(), (UINT)mMaterials.size()));
	}
}

void TexColumnsApp::BuildMaterials()
{
	auto bricks0 = std::make_unique<Material>();
	bricks0->Name = "bricks0";
	bricks0->MatCBIndex = 0;
	bricks0->DiffuseSrvHeapIndex = 0;
	bricks0->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	bricks0->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	bricks0->Roughness = 0.1f;

	auto stone0 = std::make_unique<Material>();
	stone0->Name = "stone0";
	stone0->MatCBIndex = 1;
	stone0->DiffuseSrvHeapIndex = 1;
	stone0->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	stone0->FresnelR0 = XMFLOAT3(0.05f, 0.05f, 0.05f);
	stone0->Roughness = 0.3f;

	auto tile0 = std::make_unique<Material>();
	tile0->Name = "tile0";
	tile0->MatCBIndex = 2;
	tile0->DiffuseSrvHeapIndex = 2;
	tile0->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	tile0->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	tile0->Roughness = 0.3f;

	mMaterials["bricks0"] = std::move(bricks0);
	mMaterials["stone0"] = std::move(stone0);
	mMaterials["tile0"] = std::move(tile0);
}

void TexColumnsApp::BuildRenderItems()
{
	//boxRitem->Mat = mMaterials["stone0"].get();
	/*auto boxRitem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&boxRitem->World, XMMatrixScaling(2.0f, 2.0f, 2.0f) * XMMatrixTranslation(0.0f, 1.0f, 0.0f));
	XMStoreFloat4x4(&boxRitem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	boxRitem->ObjCBIndex = 0;
	boxRitem->Mat = mMaterials["stone0"].get();
	boxRitem->Geo = mGeometries["shapeGeo"].get();
	boxRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	boxRitem->IndexCount = boxRitem->Geo->DrawArgs["box"].IndexCount;
	boxRitem->StartIndexLocation = boxRitem->Geo->DrawArgs["box"].StartIndexLocation;
	boxRitem->BaseVertexLocation = boxRitem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(boxRitem));

	auto gridRitem = std::make_unique<RenderItem>();
	gridRitem->World = MathHelper::Identity4x4();
	XMStoreFloat4x4(&gridRitem->TexTransform, XMMatrixScaling(8.0f, 8.0f, 1.0f));
	gridRitem->ObjCBIndex = 1;
	gridRitem->Mat = mMaterials["tile0"].get();
	gridRitem->Geo = mGeometries["shapeGeo"].get();
	gridRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	gridRitem->IndexCount = gridRitem->Geo->DrawArgs["grid"].IndexCount;
	gridRitem->StartIndexLocation = gridRitem->Geo->DrawArgs["grid"].StartIndexLocation;
	gridRitem->BaseVertexLocation = gridRitem->Geo->DrawArgs["grid"].BaseVertexLocation;
	mAllRitems.push_back(std::move(gridRitem));

	XMMATRIX brickTexTransform = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	UINT objCBIndex = 2;
	for (int i = 0; i < 5; ++i)
	{
		auto leftCylRitem = std::make_unique<RenderItem>();
		auto rightCylRitem = std::make_unique<RenderItem>();
		auto leftSphereRitem = std::make_unique<RenderItem>();
		auto rightSphereRitem = std::make_unique<RenderItem>();

		XMMATRIX leftCylWorld = XMMatrixTranslation(-5.0f, 1.5f, -10.0f + i * 5.0f);
		XMMATRIX rightCylWorld = XMMatrixTranslation(+5.0f, 1.5f, -10.0f + i * 5.0f);

		XMMATRIX leftSphereWorld = XMMatrixTranslation(-5.0f, 3.5f, -10.0f + i * 5.0f);
		XMMATRIX rightSphereWorld = XMMatrixTranslation(+5.0f, 3.5f, -10.0f + i * 5.0f);

		XMStoreFloat4x4(&leftCylRitem->World, rightCylWorld);
		XMStoreFloat4x4(&leftCylRitem->TexTransform, brickTexTransform);
		leftCylRitem->ObjCBIndex = objCBIndex++;
		leftCylRitem->Mat = mMaterials["bricks0"].get();
		leftCylRitem->Geo = mGeometries["shapeGeo"].get();
		leftCylRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftCylRitem->IndexCount = leftCylRitem->Geo->DrawArgs["cylinder"].IndexCount;
		leftCylRitem->StartIndexLocation = leftCylRitem->Geo->DrawArgs["cylinder"].StartIndexLocation;
		leftCylRitem->BaseVertexLocation = leftCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;

		XMStoreFloat4x4(&rightCylRitem->World, leftCylWorld);
		XMStoreFloat4x4(&rightCylRitem->TexTransform, brickTexTransform);
		rightCylRitem->ObjCBIndex = objCBIndex++;
		rightCylRitem->Mat = mMaterials["bricks0"].get();
		rightCylRitem->Geo = mGeometries["shapeGeo"].get();
		rightCylRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightCylRitem->IndexCount = rightCylRitem->Geo->DrawArgs["cylinder"].IndexCount;
		rightCylRitem->StartIndexLocation = rightCylRitem->Geo->DrawArgs["cylinder"].StartIndexLocation;
		rightCylRitem->BaseVertexLocation = rightCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;

		XMStoreFloat4x4(&leftSphereRitem->World, leftSphereWorld);
		leftSphereRitem->TexTransform = MathHelper::Identity4x4();
		leftSphereRitem->ObjCBIndex = objCBIndex++;
		leftSphereRitem->Mat = mMaterials["stone0"].get();
		leftSphereRitem->Geo = mGeometries["shapeGeo"].get();
		leftSphereRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftSphereRitem->IndexCount = leftSphereRitem->Geo->DrawArgs["sphere"].IndexCount;
		leftSphereRitem->StartIndexLocation = leftSphereRitem->Geo->DrawArgs["sphere"].StartIndexLocation;
		leftSphereRitem->BaseVertexLocation = leftSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;

		XMStoreFloat4x4(&rightSphereRitem->World, rightSphereWorld);
		rightSphereRitem->TexTransform = MathHelper::Identity4x4();
		rightSphereRitem->ObjCBIndex = objCBIndex++;
		rightSphereRitem->Mat = mMaterials["stone0"].get();
		rightSphereRitem->Geo = mGeometries["shapeGeo"].get();
		rightSphereRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightSphereRitem->IndexCount = rightSphereRitem->Geo->DrawArgs["sphere"].IndexCount;
		rightSphereRitem->StartIndexLocation = rightSphereRitem->Geo->DrawArgs["sphere"].StartIndexLocation;
		rightSphereRitem->BaseVertexLocation = rightSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;

		mAllRitems.push_back(std::move(leftCylRitem));
		mAllRitems.push_back(std::move(rightCylRitem));
		mAllRitems.push_back(std::move(leftSphereRitem));
		mAllRitems.push_back(std::move(rightSphereRitem));
	}*/

	//Back Wall
	auto boxRitem = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&boxRitem->World, XMMatrixScaling(10.0f, 20.0f, 100.0f) * XMMatrixTranslation(50.0f, 10.0f, -10.0f));

	boxRitem->ObjCBIndex = 0;
	boxRitem->Mat = mMaterials["stone0"].get();
	boxRitem->Geo = mGeometries["shapeGeo"].get();
	boxRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	boxRitem->IndexCount = boxRitem->Geo->DrawArgs["box"].IndexCount;
	boxRitem->StartIndexLocation = boxRitem->Geo->DrawArgs["box"].StartIndexLocation;
	boxRitem->BaseVertexLocation = boxRitem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(boxRitem));

	//Right wall
	auto box2Ritem = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&box2Ritem->World, XMMatrixScaling(100.0f, 20.0f, 10.0f) * XMMatrixTranslation(5.0f, 10.0f, -55.0f));

	box2Ritem->ObjCBIndex = 1;
	box2Ritem->Mat = mMaterials["stone0"].get();
	box2Ritem->Geo = mGeometries["shapeGeo"].get();
	box2Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	box2Ritem->IndexCount = box2Ritem->Geo->DrawArgs["box"].IndexCount;
	box2Ritem->StartIndexLocation = box2Ritem->Geo->DrawArgs["box"].StartIndexLocation;
	box2Ritem->BaseVertexLocation = box2Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(box2Ritem));

	//Left Wall
	auto box3Ritem = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&box3Ritem->World, XMMatrixScaling(100.0f, 20.0f, 10.0f) * XMMatrixTranslation(0.0f, 10.0f, 45.0f));

	box3Ritem->ObjCBIndex = 2;
	box3Ritem->Mat = mMaterials["stone0"].get();
	box3Ritem->Geo = mGeometries["shapeGeo"].get();
	box3Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	box3Ritem->IndexCount = box3Ritem->Geo->DrawArgs["box"].IndexCount;
	box3Ritem->StartIndexLocation = box3Ritem->Geo->DrawArgs["box"].StartIndexLocation;
	box3Ritem->BaseVertexLocation = box3Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(box3Ritem));



	//Front Wall1
	auto box4Ritem = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&box4Ritem->World, XMMatrixScaling(10.0f, 20.0f, 35.0f) * XMMatrixTranslation(-45.0f, 10.0f, -37.0f));

	box4Ritem->ObjCBIndex = 3;
	box4Ritem->Mat = mMaterials["stone0"].get();
	box4Ritem->Geo = mGeometries["shapeGeo"].get();
	box4Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	box4Ritem->IndexCount = box4Ritem->Geo->DrawArgs["box"].IndexCount;
	box4Ritem->StartIndexLocation = box4Ritem->Geo->DrawArgs["box"].StartIndexLocation;
	box4Ritem->BaseVertexLocation = box4Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(box4Ritem));

	//Front Wall2
	auto box5Ritem = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&box5Ritem->World, XMMatrixScaling(10.0f, 20.0f, 35.0f) * XMMatrixTranslation(-45.0f, 10.0f, 28.0f));

	box5Ritem->ObjCBIndex = 4;
	box5Ritem->Mat = mMaterials["stone0"].get();
	box5Ritem->Geo = mGeometries["shapeGeo"].get();
	box5Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	box5Ritem->IndexCount = box5Ritem->Geo->DrawArgs["box"].IndexCount;
	box5Ritem->StartIndexLocation = box5Ritem->Geo->DrawArgs["box"].StartIndexLocation;
	box5Ritem->BaseVertexLocation = box5Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(box5Ritem));

	//Front Wall3
	auto box6Ritem = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&box6Ritem->World, XMMatrixScaling(10.0f, 6.0f, 31.0f) * XMMatrixTranslation(-45.0f, 17.0f, -4.0f));

	box6Ritem->ObjCBIndex = 5;
	box6Ritem->Mat = mMaterials["stone0"].get();
	box6Ritem->Geo = mGeometries["shapeGeo"].get();
	box6Ritem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	box6Ritem->IndexCount = box6Ritem->Geo->DrawArgs["box"].IndexCount;
	box6Ritem->StartIndexLocation = box6Ritem->Geo->DrawArgs["box"].StartIndexLocation;
	box6Ritem->BaseVertexLocation = box6Ritem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(box6Ritem));

	//Front Merlins
	auto FMerlin1 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FMerlin1->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-40.0f, 22.0f, -25.0f));

	FMerlin1->ObjCBIndex = 6;
	FMerlin1->Mat = mMaterials["tile0"].get();
	FMerlin1->Geo = mGeometries["shapeGeo"].get();
	FMerlin1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FMerlin1->IndexCount = FMerlin1->Geo->DrawArgs["box"].IndexCount;
	FMerlin1->StartIndexLocation = FMerlin1->Geo->DrawArgs["box"].StartIndexLocation;
	FMerlin1->BaseVertexLocation = FMerlin1->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FMerlin1));

	auto FMerlin2 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FMerlin2->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-40.0f, 22.0f, -5.0f));

	FMerlin2->ObjCBIndex = 7;
	FMerlin2->Mat = mMaterials["tile0"].get();
	FMerlin2->Geo = mGeometries["shapeGeo"].get();
	FMerlin2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FMerlin2->IndexCount = FMerlin2->Geo->DrawArgs["box"].IndexCount;
	FMerlin2->StartIndexLocation = FMerlin2->Geo->DrawArgs["box"].StartIndexLocation;
	FMerlin2->BaseVertexLocation = FMerlin2->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FMerlin2));

	auto FMerlin3 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FMerlin3->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-40.0f, 22.0f, 15.0f));

	FMerlin3->ObjCBIndex = 8;
	FMerlin3->Mat = mMaterials["tile0"].get();
	FMerlin3->Geo = mGeometries["shapeGeo"].get();
	FMerlin3->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FMerlin3->IndexCount = FMerlin3->Geo->DrawArgs["box"].IndexCount;
	FMerlin3->StartIndexLocation = FMerlin3->Geo->DrawArgs["box"].StartIndexLocation;
	FMerlin3->BaseVertexLocation = FMerlin3->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FMerlin3));

	auto FMerlin4 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FMerlin4->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, 23.0f));

	FMerlin4->ObjCBIndex = 9;
	FMerlin4->Mat = mMaterials["tile0"].get();
	FMerlin4->Geo = mGeometries["shapeGeo"].get();
	FMerlin4->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FMerlin4->IndexCount = FMerlin4->Geo->DrawArgs["box"].IndexCount;
	FMerlin4->StartIndexLocation = FMerlin4->Geo->DrawArgs["box"].StartIndexLocation;
	FMerlin4->BaseVertexLocation = FMerlin4->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FMerlin4));

	auto FMerlin5 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FMerlin5->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, 3.0f));

	FMerlin5->ObjCBIndex = 10;
	FMerlin5->Mat = mMaterials["tile0"].get();
	FMerlin5->Geo = mGeometries["shapeGeo"].get();
	FMerlin5->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FMerlin5->IndexCount = FMerlin5->Geo->DrawArgs["box"].IndexCount;
	FMerlin5->StartIndexLocation = FMerlin5->Geo->DrawArgs["box"].StartIndexLocation;
	FMerlin5->BaseVertexLocation = FMerlin5->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FMerlin5));

	auto FMerlin6 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FMerlin6->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, -17.0f));

	FMerlin6->ObjCBIndex = 11;
	FMerlin6->Mat = mMaterials["tile0"].get();
	FMerlin6->Geo = mGeometries["shapeGeo"].get();
	FMerlin6->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FMerlin6->IndexCount = FMerlin6->Geo->DrawArgs["box"].IndexCount;
	FMerlin6->StartIndexLocation = FMerlin6->Geo->DrawArgs["box"].StartIndexLocation;
	FMerlin6->BaseVertexLocation = FMerlin6->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FMerlin6));

	auto FMerlin7 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FMerlin7->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(-50.0f, 22.0f, -37.0f));

	FMerlin7->ObjCBIndex = 12;
	FMerlin7->Mat = mMaterials["tile0"].get();
	FMerlin7->Geo = mGeometries["shapeGeo"].get();
	FMerlin7->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FMerlin7->IndexCount = FMerlin7->Geo->DrawArgs["box"].IndexCount;
	FMerlin7->StartIndexLocation = FMerlin7->Geo->DrawArgs["box"].StartIndexLocation;
	FMerlin7->BaseVertexLocation = FMerlin7->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FMerlin7));

	//Front Crenel
	auto FCrenel1 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FCrenel1->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(-50.2f, 20.0f, -4.0f));

	FCrenel1->ObjCBIndex = 13;
	FCrenel1->Mat = mMaterials["bricks0"].get();
	FCrenel1->Geo = mGeometries["shapeGeo"].get();
	FCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FCrenel1->IndexCount = FCrenel1->Geo->DrawArgs["box"].IndexCount;
	FCrenel1->StartIndexLocation = FCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
	FCrenel1->BaseVertexLocation = FCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FCrenel1));

	auto FCrenel2 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&FCrenel2->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(-40.2f, 20.0f, -4.0f));

	FCrenel2->ObjCBIndex = 14;
	FCrenel2->Mat = mMaterials["bricks0"].get();
	FCrenel2->Geo = mGeometries["shapeGeo"].get();
	FCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	FCrenel2->IndexCount = FCrenel2->Geo->DrawArgs["box"].IndexCount;
	FCrenel2->StartIndexLocation = FCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
	FCrenel2->BaseVertexLocation = FCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(FCrenel2));

	//Back Merlins
	auto BMerlin1 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BMerlin1->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(45.0f, 22.0f, -25.0f));

	BMerlin1->ObjCBIndex = 15;
	BMerlin1->Mat = mMaterials["tile0"].get();
	BMerlin1->Geo = mGeometries["shapeGeo"].get();
	BMerlin1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BMerlin1->IndexCount = BMerlin1->Geo->DrawArgs["box"].IndexCount;
	BMerlin1->StartIndexLocation = BMerlin1->Geo->DrawArgs["box"].StartIndexLocation;
	BMerlin1->BaseVertexLocation = BMerlin1->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BMerlin1));

	auto BMerlin2 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BMerlin2->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(45.0f, 22.0f, -5.0f));

	BMerlin2->ObjCBIndex = 16;
	BMerlin2->Mat = mMaterials["tile0"].get();
	BMerlin2->Geo = mGeometries["shapeGeo"].get();
	BMerlin2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BMerlin2->IndexCount = BMerlin2->Geo->DrawArgs["box"].IndexCount;
	BMerlin2->StartIndexLocation = BMerlin2->Geo->DrawArgs["box"].StartIndexLocation;
	BMerlin2->BaseVertexLocation = BMerlin2->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BMerlin2));

	auto BMerlin3 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BMerlin3->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(45.0f, 22.0f, 15.0f));

	BMerlin3->ObjCBIndex = 17;
	BMerlin3->Mat = mMaterials["tile0"].get();
	BMerlin3->Geo = mGeometries["shapeGeo"].get();
	BMerlin3->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BMerlin3->IndexCount = BMerlin3->Geo->DrawArgs["box"].IndexCount;
	BMerlin3->StartIndexLocation = BMerlin3->Geo->DrawArgs["box"].StartIndexLocation;
	BMerlin3->BaseVertexLocation = BMerlin3->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BMerlin3));

	auto BMerlin4 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BMerlin4->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, 23.0f));

	BMerlin4->ObjCBIndex = 18;
	BMerlin4->Mat = mMaterials["tile0"].get();
	BMerlin4->Geo = mGeometries["shapeGeo"].get();
	BMerlin4->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BMerlin4->IndexCount = BMerlin4->Geo->DrawArgs["box"].IndexCount;
	BMerlin4->StartIndexLocation = BMerlin4->Geo->DrawArgs["box"].StartIndexLocation;
	BMerlin4->BaseVertexLocation = BMerlin4->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BMerlin4));

	auto BMerlin5 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BMerlin5->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, 3.0f));

	BMerlin5->ObjCBIndex = 19;
	BMerlin5->Mat = mMaterials["tile0"].get();
	BMerlin5->Geo = mGeometries["shapeGeo"].get();
	BMerlin5->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BMerlin5->IndexCount = BMerlin5->Geo->DrawArgs["box"].IndexCount;
	BMerlin5->StartIndexLocation = BMerlin5->Geo->DrawArgs["box"].StartIndexLocation;
	BMerlin5->BaseVertexLocation = BMerlin5->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BMerlin5));

	auto BMerlin6 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BMerlin6->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, -17.0f));

	BMerlin6->ObjCBIndex = 20;
	BMerlin6->Mat = mMaterials["tile0"].get();
	BMerlin6->Geo = mGeometries["shapeGeo"].get();
	BMerlin6->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BMerlin6->IndexCount = BMerlin6->Geo->DrawArgs["box"].IndexCount;
	BMerlin6->StartIndexLocation = BMerlin6->Geo->DrawArgs["box"].StartIndexLocation;
	BMerlin6->BaseVertexLocation = BMerlin6->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BMerlin6));

	auto BMerlin7 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BMerlin7->World, XMMatrixScaling(1.0f, 6.0f, 15.0f) * XMMatrixTranslation(55.0f, 22.0f, -37.0f));

	BMerlin7->ObjCBIndex = 21;
	BMerlin7->Mat = mMaterials["tile0"].get();
	BMerlin7->Geo = mGeometries["shapeGeo"].get();
	BMerlin7->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BMerlin7->IndexCount = BMerlin7->Geo->DrawArgs["box"].IndexCount;
	BMerlin7->StartIndexLocation = BMerlin7->Geo->DrawArgs["box"].StartIndexLocation;
	BMerlin7->BaseVertexLocation = BMerlin7->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BMerlin7));

	//Back Crenel
	auto BCrenel1 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BCrenel1->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(55.2f, 20.0f, -4.0f));

	BCrenel1->ObjCBIndex = 22;
	BCrenel1->Mat = mMaterials["bricks0"].get();
	BCrenel1->Geo = mGeometries["shapeGeo"].get();
	BCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BCrenel1->IndexCount = BCrenel1->Geo->DrawArgs["box"].IndexCount;
	BCrenel1->StartIndexLocation = BCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
	BCrenel1->BaseVertexLocation = BCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BCrenel1));
	//
	auto BCrenel2 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&BCrenel2->World, XMMatrixScaling(0.5f, 4.0f, 100.0f) * XMMatrixTranslation(45.2f, 20.0f, -4.0f));

	BCrenel2->ObjCBIndex = 23;
	BCrenel2->Mat = mMaterials["bricks0"].get();
	BCrenel2->Geo = mGeometries["shapeGeo"].get();
	BCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	BCrenel2->IndexCount = BCrenel2->Geo->DrawArgs["box"].IndexCount;
	BCrenel2->StartIndexLocation = BCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
	BCrenel2->BaseVertexLocation = BCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(BCrenel2));
	////

	auto gridRitem = std::make_unique<RenderItem>();

	gridRitem->World = MathHelper::Identity4x4();
	gridRitem->ObjCBIndex = 24;
	gridRitem->Mat = mMaterials["bricks0"].get();
	gridRitem->Geo = mGeometries["shapeGeo"].get();
	gridRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	gridRitem->IndexCount = gridRitem->Geo->DrawArgs["grid"].IndexCount;
	gridRitem->StartIndexLocation = gridRitem->Geo->DrawArgs["grid"].StartIndexLocation;
	gridRitem->BaseVertexLocation = gridRitem->Geo->DrawArgs["grid"].BaseVertexLocation;

	mAllRitems.push_back(std::move(gridRitem));

	//Left crenal

	auto LCrenel1 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&LCrenel1->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(1.0f, 20.0f, 40.0f));

	LCrenel1->ObjCBIndex = 25;
	LCrenel1->Mat = mMaterials["bricks0"].get();
	LCrenel1->Geo = mGeometries["shapeGeo"].get();
	LCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	LCrenel1->IndexCount = LCrenel1->Geo->DrawArgs["box"].IndexCount;
	LCrenel1->StartIndexLocation = LCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
	LCrenel1->BaseVertexLocation = LCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(LCrenel1));

	auto LCrenel2 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&LCrenel2->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(1.0f, 20.0f, 50.0f));

	LCrenel2->ObjCBIndex = 26;
	LCrenel2->Mat = mMaterials["bricks0"].get();
	LCrenel2->Geo = mGeometries["shapeGeo"].get();
	LCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	LCrenel2->IndexCount = LCrenel2->Geo->DrawArgs["box"].IndexCount;
	LCrenel2->StartIndexLocation = LCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
	LCrenel2->BaseVertexLocation = LCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(LCrenel2));


	//Right crenel
	auto RCrenel1 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&RCrenel1->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(5.0f, 20.0f, -50.0f));

	RCrenel1->ObjCBIndex = 27;
	RCrenel1->Mat = mMaterials["bricks0"].get();
	RCrenel1->Geo = mGeometries["shapeGeo"].get();
	RCrenel1->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	RCrenel1->IndexCount = RCrenel1->Geo->DrawArgs["box"].IndexCount;
	RCrenel1->StartIndexLocation = RCrenel1->Geo->DrawArgs["box"].StartIndexLocation;
	RCrenel1->BaseVertexLocation = RCrenel1->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(RCrenel1));

	auto RCrenel2 = std::make_unique<RenderItem>();

	XMStoreFloat4x4(&RCrenel2->World, XMMatrixScaling(100.0f, 4.0f, 0.5f) * XMMatrixTranslation(5.0f, 20.0f, -60.0f));

	RCrenel2->ObjCBIndex = 28;
	RCrenel2->Mat = mMaterials["bricks0"].get();
	RCrenel2->Geo = mGeometries["shapeGeo"].get();
	RCrenel2->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	RCrenel2->IndexCount = RCrenel2->Geo->DrawArgs["box"].IndexCount;
	RCrenel2->StartIndexLocation = RCrenel2->Geo->DrawArgs["box"].StartIndexLocation;
	RCrenel2->BaseVertexLocation = RCrenel2->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(RCrenel2));



	UINT objCBIndex = 29;



	for (int i = 0; i < 2; ++i)
	{
		auto leftCylRitem = std::make_unique<RenderItem>();
		auto rightCylRitem = std::make_unique<RenderItem>();

		auto leftConeRitem = std::make_unique<RenderItem>();
		auto rightConeRitem = std::make_unique<RenderItem>();

		auto leftSphereRitem = std::make_unique<RenderItem>();
		auto rightSphereRitem = std::make_unique<RenderItem>();

		XMMATRIX leftSphereWorld = XMMatrixTranslation(-45.0f, 30.0f, -53.0f + i * 97.0f);
		XMMATRIX rightSphereWorld = XMMatrixTranslation(+50.0f, 30.0f, -53.0f + i * 97.0f);

		XMMATRIX leftCylWorld = XMMatrixTranslation(-45.0f, 15.0f, -53.0f + i * 97.0f);
		XMMATRIX rightCylWorld = XMMatrixTranslation(+50.0f, 15.0f, -53.0f + i * 97.0f);

		XMMATRIX leftConeWorld = XMMatrixTranslation(-45.0f, 15.0f, -53.0f + i * 97.0f);
		XMMATRIX rightConeWorld = XMMatrixTranslation(+50.0f, 15.0f, -53.0f + i * 97.0f);

		XMStoreFloat4x4(&leftCylRitem->World, rightCylWorld);

		leftCylRitem->ObjCBIndex = objCBIndex++;

		leftCylRitem->Mat = mMaterials["bricks0"].get();
		leftCylRitem->Geo = mGeometries["shapeGeo"].get();
		leftCylRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftCylRitem->IndexCount = leftCylRitem->Geo->DrawArgs["cylinder"].IndexCount;
		leftCylRitem->StartIndexLocation = leftCylRitem->Geo->DrawArgs["cylinder"].StartIndexLocation;
		leftCylRitem->BaseVertexLocation = leftCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;

		XMStoreFloat4x4(&rightCylRitem->World, leftCylWorld);

		rightCylRitem->ObjCBIndex = objCBIndex++;

		rightCylRitem->Mat = mMaterials["bricks0"].get();
		rightCylRitem->Geo = mGeometries["shapeGeo"].get();
		rightCylRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightCylRitem->IndexCount = rightCylRitem->Geo->DrawArgs["cylinder"].IndexCount;
		rightCylRitem->StartIndexLocation = rightCylRitem->Geo->DrawArgs["cylinder"].StartIndexLocation;
		rightCylRitem->BaseVertexLocation = rightCylRitem->Geo->DrawArgs["cylinder"].BaseVertexLocation;

		/*XMStoreFloat4x4(&leftConeRitem->World, rightConeWorld);

		leftConeRitem->ObjCBIndex = objCBIndex++;
		leftConeRitem->Geo = mGeometries["shapeGeo"].get();
		leftConeRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftConeRitem->IndexCount = leftConeRitem->Geo->DrawArgs["cone"].IndexCount;
		leftConeRitem->StartIndexLocation = leftConeRitem->Geo->DrawArgs["cone"].StartIndexLocation;
		leftConeRitem->BaseVertexLocation = leftConeRitem->Geo->DrawArgs["cone"].BaseVertexLocation;

		XMStoreFloat4x4(&rightConeRitem->World, leftCylWorld);

		rightConeRitem->ObjCBIndex = objCBIndex++;

		rightConeRitem->Geo = mGeometries["shapeGeo"].get();
		rightConeRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightConeRitem->IndexCount = rightConeRitem->Geo->DrawArgs["cone"].IndexCount;
		rightConeRitem->StartIndexLocation = rightConeRitem->Geo->DrawArgs["cone"].StartIndexLocation;
		rightConeRitem->BaseVertexLocation = rightConeRitem->Geo->DrawArgs["cone"].BaseVertexLocation;*/

		XMStoreFloat4x4(&leftSphereRitem->World, leftSphereWorld);

		leftSphereRitem->ObjCBIndex = objCBIndex++;
		leftSphereRitem->Mat = mMaterials["stone0"].get();
		leftSphereRitem->Geo = mGeometries["shapeGeo"].get();
		leftSphereRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		leftSphereRitem->IndexCount = leftSphereRitem->Geo->DrawArgs["sphere"].IndexCount;
		leftSphereRitem->StartIndexLocation = leftSphereRitem->Geo->DrawArgs["sphere"].StartIndexLocation;
		leftSphereRitem->BaseVertexLocation = leftSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;

		XMStoreFloat4x4(&rightSphereRitem->World, rightSphereWorld);

		rightSphereRitem->ObjCBIndex = objCBIndex++;

		rightSphereRitem->Mat = mMaterials["stone0"].get();
		rightSphereRitem->Geo = mGeometries["shapeGeo"].get();
		rightSphereRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		rightSphereRitem->IndexCount = rightSphereRitem->Geo->DrawArgs["sphere"].IndexCount;
		rightSphereRitem->StartIndexLocation = rightSphereRitem->Geo->DrawArgs["sphere"].StartIndexLocation;
		rightSphereRitem->BaseVertexLocation = rightSphereRitem->Geo->DrawArgs["sphere"].BaseVertexLocation;

		mAllRitems.push_back(std::move(leftCylRitem));
		mAllRitems.push_back(std::move(rightCylRitem));
		/*mAllRitems.push_back(std::move(leftConeRitem));
		mAllRitems.push_back(std::move(rightConeRitem));*/
		mAllRitems.push_back(std::move(leftSphereRitem));
		mAllRitems.push_back(std::move(rightSphereRitem));
	}

	// All the render items are opaque.
	for (auto& e : mAllRitems)
		mOpaqueRitems.push_back(e.get());
}

void TexColumnsApp::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems)
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = mCurrFrameResource->ObjectCB->Resource();
	auto matCB = mCurrFrameResource->MaterialCB->Resource();

	// For each render item...
	for (size_t i = 0; i < ritems.size(); ++i)
	{
		auto ri = ritems[i];

		cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
		cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
		cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(ri->Mat->DiffuseSrvHeapIndex, mCbvSrvDescriptorSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + ri->Mat->MatCBIndex * matCBByteSize;

		cmdList->SetGraphicsRootDescriptorTable(0, tex);
		cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
		cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

		cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
	}
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> TexColumnsApp::GetStaticSamplers()
{
	// Applications usually only need a handful of samplers.  So just define them all up front
	// and keep them available as part of the root signature.  

	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	return {
		pointWrap, pointClamp,
		linearWrap, linearClamp,
		anisotropicWrap, anisotropicClamp };
}

