#include "glwidget.h"

#include "sphere.h"
#include "cs123_lib/resourceloader.h"
#include "cs123_lib/errorchecker.h"
#include "settings.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include "openglshape.h"
#include "gl/shaders/ShaderAttribLocations.h"

#define PI 3.14159265f

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_program(0),
      m_sphere(nullptr),
      m_angleX(-0.5f),
      m_angleY(0.5f),
      m_zoom(4.f)
{}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    resizeGL(width(), height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Creates the shader program that will be used for drawing.
    m_program = ResourceLoader::createShaderProgram(":/shaders/shader.vert", ":/shaders/shader.frag");

    // Initialize sphere with radius 0.5 centered at origin.
    std::vector<GLfloat> sphereData = SPHERE_VERTEX_POSITIONS;
    m_sphere = std::make_unique<OpenGLShape>();

    m_sphere->setVertexData(&sphereData[0], sphereData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_SPHERE_VERTICES);
    m_sphere->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_sphere->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, true);
    m_sphere->buildVAO();
}

void GLWidget::paintGL() {
    // Clear the color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model(1.f);
    ErrorChecker::printGLErrors("Kmilo1");
 glUseProgram(m_program);
     ErrorChecker::printGLErrors("Kmilo2");
    // Sets projection and view matrix uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    ErrorChecker::printGLErrors("Kmilo3");
    glUniformMatrix4fv(glGetUniformLocation(m_program, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
ErrorChecker::printGLErrors("Kmilo4");
    // Sets uniforms that are controlled by the UI.
    glUniform1f(glGetUniformLocation(m_program, "shininess"), settings.shininess);
    ErrorChecker::printGLErrors("Kmilo5");
    glUniform1f(glGetUniformLocation(m_program, "lightIntensity"), settings.lightIntensity);
    ErrorChecker::printGLErrors("Kmilo6");
    glUniform3f(glGetUniformLocation(m_program, "lightColor"),
                settings.lightColor.redF(),
                settings.lightColor.greenF(),
                settings.lightColor.blueF());
    glUniform1f(glGetUniformLocation(m_program, "attQuadratic"), settings.attQuadratic);
    ErrorChecker::printGLErrors("Kmilo7");
    glUniform1f(glGetUniformLocation(m_program, "attLinear"), settings.attLinear);
    ErrorChecker::printGLErrors("Kmilo8");
    glUniform1f(glGetUniformLocation(m_program, "attConstant"), settings.attConstant);
    ErrorChecker::printGLErrors("Kmilo9");
    glUniform1f(glGetUniformLocation(m_program, "ambientIntensity"), settings.ambientIntensity);
    ErrorChecker::printGLErrors("Kmilo10");
    glUniform1f(glGetUniformLocation(m_program, "diffuseIntensity"), settings.diffuseIntensity);
    ErrorChecker::printGLErrors("Kmilo11");
    glUniform1f(glGetUniformLocation(m_program, "specularIntensity"), settings.specularIntensity);
ErrorChecker::printGLErrors("Kmilo12");

     glm::vec3 viewPos(m_view[0][3],m_view[1][3],m_view[2][3]);
     glUniform3fv(glGetUniformLocation(m_program, "CameraSpace_position"),1, glm::value_ptr(viewPos));
     ErrorChecker::printGLErrors("Kmilo22 ");
    //glUseProgram(0);

    // Draws a sphere at the origin.
    model = glm::mat4(1.f);
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    ErrorChecker::printGLErrors("Kmilo13 ");
    glm::vec3 sphereMColor(
                    settings.sphereMColor.redF(),
                    settings.sphereMColor.greenF(),
                    settings.sphereMColor.blueF());

    glUniform3fv(glGetUniformLocation(m_program, "color"),1,
                glm::value_ptr(sphereMColor));

    ErrorChecker::printGLErrors("Kmilo14 ");
    rebuildMatrices();
    ErrorChecker::printGLErrors("Kmilo15");

    m_sphere->draw();
    ErrorChecker::printGLErrors("Kmilo16");

    model = glm::translate(model,glm::vec3(-1.5,0,0));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    ErrorChecker::printGLErrors("Kmilo3");
    glUniformMatrix4fv(glGetUniformLocation(m_program, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glm::vec3 sphereLColor(
                    settings.sphereLColor.redF(),
                    settings.sphereLColor.greenF(),
                    settings.sphereLColor.blueF());

    glUniform3fv(glGetUniformLocation(m_program, "color"),1,
                glm::value_ptr(sphereLColor));
    m_sphere->draw();

    model = glm::mat4(1.f);
    glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    ErrorChecker::printGLErrors("Kmilo3");
    glUniformMatrix4fv(glGetUniformLocation(m_program, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    model = glm::translate(model,glm::vec3(1.5,0,0));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glm::vec3 sphereRColor(
                    settings.sphereRColor.redF(),
                    settings.sphereRColor.greenF(),
                    settings.sphereRColor.blueF());

    glUniform3fv(glGetUniformLocation(m_program, "color"),1,
                glm::value_ptr(sphereRColor));
    m_sphere->draw();

    // glUseProgram(0);
    // TODO: Draw two more spheres. (Task 2)

}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    m_prevMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    m_angleX += 3 * (event->x() - m_prevMousePos.x()) / (float) width();
    m_angleY += 3 * (event->y() - m_prevMousePos.y()) / (float) height();
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    m_zoom -= event->delta() / 100.f;
    rebuildMatrices();
}

void GLWidget::rebuildMatrices() {
    m_view = glm::translate(glm::vec3(0, 0, -m_zoom)) *
             glm::rotate(m_angleY, glm::vec3(1,0,0)) *
             glm::rotate(m_angleX, glm::vec3(0,1,0));

    m_projection = glm::perspective(0.8f, (float)width()/height(), 0.1f, 100.f);
    update();
}
