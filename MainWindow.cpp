#include "MainWindows.h"

LRESULT CALLBACK MainWindow::WindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
	MainWindow* p_this = nullptr;

	if (u_msg == WM_NCCREATE)
	{
		const auto pCreate = reinterpret_cast<CREATESTRUCT*>(l_param);
		p_this = static_cast<MainWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_this));

		p_this->m_hwnd = hwnd;
	}
	else
	{
		p_this = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}
	if (p_this)
	{
		return p_this->HandleMessage(u_msg, w_param, l_param);
	}
	return DefWindowProc(hwnd, u_msg, w_param, l_param);
}

PCWSTR MainWindow::ClassName() { return L"El Window"; }

MainWindow::MainWindow(
	PCWSTR lp_window_name,
	DWORD dw_style,
	DWORD dw_ex_style,
	int x,
	int y,
	int n_width,
	int n_height,
	HWND h_wnd_parent,
	HMENU h_menu
)
{
	WNDCLASS wc = {0};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = ClassName();

	RegisterClass(&wc);

	m_hwnd = CreateWindowEx(
		dw_ex_style, ClassName(), lp_window_name, dw_style, x, y,
		n_width, n_height, h_wnd_parent, h_menu, GetModuleHandle(nullptr), this
	);
	ShowWindow(m_hwnd, SW_SHOW);
	m_renderer = std::make_unique<Renderer>(m_hwnd);
}


LRESULT MainWindow::HandleMessage(const UINT u_msg, const WPARAM w_param, const LPARAM l_param) const
{
	switch (u_msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			const HDC hdc = BeginPaint(m_hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1)));
			EndPaint(m_hwnd, &ps);
		}
		return 0;

	default:
		return DefWindowProc(m_hwnd, u_msg, w_param, l_param);
	}
	return true;
}

HWND MainWindow::GetWindowHandle() const { return m_hwnd; }
