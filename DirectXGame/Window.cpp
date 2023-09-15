#include "Window.h"

// Window* window=nullptr;

Window::Window() {}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  switch (msg) {
    case WM_CREATE: {
      // Event fired when the window is created
      // collected here..
      Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
      // .. and then stored for later lookup
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
      window->set_hwnd(hwnd);
      window->OnCreate();
      break;
    }

    case WM_DESTROY: {
      // Event fired when the window is destroyed
      Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
      window->OnDestroy();
      ::PostQuitMessage(0);
      break;
    }

    default:
      return ::DefWindowProc(hwnd, msg, wparam, lparam);
  }

  return NULL;
}

bool Window::Init() {
  // Setting up WNDCLASSEX object
  WNDCLASSEX wc;
  wc.cbClsExtra = NULL;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.cbWndExtra = NULL;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wc.hInstance = NULL;
  wc.lpszClassName = L"MyWindowClass";
  wc.lpszMenuName = L"";
  wc.style = NULL;
  wc.lpfnWndProc = &WndProc;

  if (!RegisterClassEx(&wc))  // If the registration of class will fail, the
                                // function will return false
    return false;

  // Creation of the window
  hwnd_ = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass",
                            L"DirectX Application", WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL,
                            NULL, this);

  // if the creation fail return false
  if (!hwnd_) return false;

  // show up the window
  ShowWindow(hwnd_, SW_SHOW);
  UpdateWindow(hwnd_);

  // set this flag to true to indicate that the window is initialized and
  // running
  is_run_ = true;

  return true;
}

bool Window::Broadcast() {
  MSG msg;

  this->OnUpdate();

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  Sleep(1);

  return true;
}

bool Window::Release() {
  // Destroy the window
  if (!DestroyWindow(hwnd_)) return false;

  return true;
}

bool Window::IsRun() { return is_run_; }

RECT Window::GetClientWindowRect() { 
  RECT rect;
  GetClientRect(hwnd_, &rect);
  return rect;
}

void Window::set_hwnd(HWND hwnd) { this->hwnd_ = hwnd; }

void Window::OnCreate() {}

void Window::OnUpdate() {}

void Window::OnDestroy() { is_run_ = false; }

Window::~Window() {}
