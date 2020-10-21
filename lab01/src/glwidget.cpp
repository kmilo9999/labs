#include "glwidget.h"
#include "settings.h"
#include <math.h>

#include "cs123_lib/resourceloader.h"
#include "openglshape.h"

#include "gl/shaders/ShaderAttribLocations.h"
#include <math.h>

using namespace CS123::GL;

#define PI 3.14159265

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_program(0),
      m_triangle(nullptr),
      m_strip(nullptr),
      m_fan(nullptr)
{

}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    m_program = ResourceLoader::createShaderProgram(":/shaders/shader.vert", ":/shaders/shader.frag");
    glViewport(0, 0, width(), height());
    glEnable(GL_CULL_FACE); // Hides the back faces of triangles.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Defines the color the screen will be cleared to.

    initializeTriangle();
    initializeStrip();
    initializeFan();
}

void GLWidget::paintGL() {
    glUseProgram(m_program);       // Installs the shader program. You'll learn about this later.
    glClear(GL_COLOR_BUFFER_BIT);  // Clears the color buffer. (i.e. Sets the screen to black.)

    // This draws only the lines of the triangles if "Draw lines only" is checked. Otherwise they
    // are filled in like normal.
    glPolygonMode(GL_FRONT_AND_BACK, settings.linesEnabled ? GL_LINE : GL_FILL);

    // TODO [Task 8-10]: Draw shapes in the appropriate switch case.

    switch (settings.shape) {
        case SHAPE_TRIANGLE:
            m_triangle->draw();
            break;
        case SHAPE_TRIANGLE_STRIP:
            m_strip->draw();
            break;
        case SHAPE_TRIANGLE_FAN:
            m_fan->draw();
            break;
    }

    glUseProgram(0); // Uninstalls the shader program.
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::initializeTriangle() {
    m_triangle = std::make_unique<OpenGLShape>();

    // TODO [Task 7]
    std::vector<float> myTriangle{-0.5,-0.5,0.0,0.5,-0.5,0.0,0.0,0.5,0.0};
    m_triangle->setVertexData(&myTriangle[0],9,VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES,3);
    m_triangle->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT,GL_FALSE);
    m_triangle->buildVAO();
}

void GLWidget::initializeStrip() {
    m_strip = std::make_unique<OpenGLShape>();

    // TODO [Task 9]
    std::vector<float> myStripTriangle{-0.5,0.5,0.0,
                                  -0.5,-0.5,0.0,
                                  0.0,0.5,0.0,
                                  0.0,-0.5,0.0,
                                  0.5,0.5,0.0,
                                  0.5,-0.5,0.0,
                                  };

    m_strip->setVertexData(&myStripTriangle[0],myStripTriangle.size(),VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP,6);
    m_strip->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT,GL_FALSE);
    m_strip->buildVAO();
}

void GLWidget::initializeFan() {
    m_fan.reset(new OpenGLShape());

    // TODO [Task 10]
//    std::vector<float> myTriangleFan{0.0,0.0,0.0,
//                                    0.0,0.5,0.0,
//                                    -0.5,0.25,0.0,
//                                    -0.5,-0.25,0.0,
//                                    0.0,-0.5,0.0,
//                                    0.5,-0.25,0.0,
//                                    0.5,0.25,0.0,
//                                    0.0,0.5,0.0
//                                    };

   std::vector<float> myTriangleFan {0.0,0.0,0.0};

   for(int i = 360; i >= 0 ;--i)
   {
     myTriangleFan.push_back(sinf(i * PI/180));
     myTriangleFan.push_back(cosf(i * PI/180));
     myTriangleFan.push_back(0);

   }

   myTriangleFan.push_back(sinf(0));
   myTriangleFan.push_back(cosf(0));
   myTriangleFan.push_back(0);


   m_fan->setVertexData(&myTriangleFan[0],myTriangleFan.size(),VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_FAN,myTriangleFan.size()/3);
   m_fan->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT,GL_FALSE);
   m_fan->buildVAO();
}
