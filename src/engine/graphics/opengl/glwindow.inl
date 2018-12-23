
namespace amalgamation {

    static void glfwError(int id, const char* description)
    {
        errorln("glfw: ", id, " desc: ", description);
    }

    GLWindow::GLWindow()
        : Window(API::opengl),
        _window(nullptr), _monitor(nullptr), _mode(nullptr) {}

    GLWindow::GLWindow(const std::string& title, std::size_t width, std::size_t height, bool fullscreen)
        : Window(title, width, height, fullscreen, API::opengl),
        _window(nullptr), _monitor(nullptr), _mode(nullptr) {}

    GLWindow::~GLWindow() {
        if(GLFWInstance::open_windows() == 0) {
            GLFWInstance::terminate();
        }
    }

    bool GLWindow::open() {

        this->_valid = false;

        if(!GLFWInstance::is_initialized()) {
            if(!GLFWInstance::init()) {
                glerrorln("Failed to init glfw!");
                return false;
            }
        } else {
            if(this->_window != nullptr) {
                glfwSetWindowShouldClose(this->_window, GLFW_TRUE);
                GLFWInstance::open_windows(true, GLFWInstance::open_windows() - 1);
            }
        }

        glfwSetErrorCallback(&glfwError);

        this->_monitor = glfwGetPrimaryMonitor();
        this->_mode    = glfwGetVideoMode(this->_monitor);

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->_window = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), this->_fullscreen ? this->_monitor : nullptr, nullptr);

        if(this->_window == nullptr) {
            glerrorln("Failed to create glfw window!");
            return false;
        }

        GLFWInstance::open_windows(true, GLFWInstance::open_windows() + 1);

        glfwMakeContextCurrent(this->_window);
        glfwSetWindowUserPointer(this->_window, this);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            glerrorln("Failed to initialize glad!");
            return false;
        }

        GLCALL(glEnable(GL_DEPTH_TEST));
        GLCALL(glEnable(GL_MULTISAMPLE));
        
        this->_valid = true;

        return true;
    }

    bool GLWindow::open(const std::string& title, std::size_t width, std::size_t height, bool fullscreen) {

        this->_title      = title;
        this->_width      = width;
        this->_height     = height;
        this->_fullscreen = fullscreen;

        return this->open();

    }

    bool GLWindow::update() {
		if (!glfwWindowShouldClose(this->_window) && this->_valid) {
			glfwGetFramebufferSize(this->_window, reinterpret_cast<int*>(&this->_width), reinterpret_cast<int*>(&this->_height));
			glfwSwapBuffers(this->_window);
			glfwPollEvents();
			GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
            return true;
		} else {
			this->_valid = false;
            GLFWInstance::open_windows(true, GLFWInstance::open_windows() - 1);
            return false;
        }
    }
    
    bool GLWindow::close() {
        if(!this->_valid) {
            return false;
        } else {
            this->_valid = false;
            glfwSetWindowShouldClose(this->_window, GLFW_TRUE);
            GLFWInstance::open_windows(true, GLFWInstance::open_windows() - 1);
            return true;
        }
    }

    void GLWindow::resize(std::size_t width, std::size_t height) {
        if(!this->_fullscreen) {
            glfwSetWindowSize(this->_window, width, height);
        } else {
            glfwSetWindowMonitor(this->_window, this->_monitor, 0, 0, width, height, this->_mode->refreshRate);
        }
        this->_width  = width;
        this->_height = height;
    }

}