#include "Renderer.h"
#include "Interfaces/IDevice.h"
GraphicsAPI Renderer::s_GraphicsAPI = GraphicsAPI::DX11;

Renderer::Renderer(HWND hwnd)
{
	p_Device = IDevice::Create();
	p_SwapChain = ISwapChain::Create(p_Device, hwnd);
	

	//get the texture from the swap chain (back buffer) buffer #0

}

void Renderer::EndFrame()
{
	p_Device->Present(1u, 0u);
}

Renderer::~Renderer()
{
	if (p_render_target_view != nullptr) {
		p_render_target_view->Release();
	}
	if (p_SwapChain != nullptr) {
		p_SwapChain->Release();
	}
}

void Renderer::ClearRenderTargetView(float red, float green, float blue, float alpha)
{
	float color[4] = { red, green, blue, alpha };
	p_Device_Context->ClearRenderTargetView(p_render_target_view, color);
}
