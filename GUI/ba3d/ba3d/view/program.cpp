// GPL3; https://github.com/jburle/ba3d

#include "program.h"
#include "camera.h"
#include <QMatrix4x4>

namespace ba3d {
//------------------------------------------------------------------------------

Program::Program() {
  needsInit();
}

void Program::needsInit() {
  doInit = true;
}

namespace {
static char const *shaderVertex =
  "attribute vec3 vertex;"
  "attribute vec3 normal;"
  "uniform   mat4 matProj, matModel, matObject;"
  "varying   vec3 vo, nm;"

  "void main() {"
  "  vec4 vertObj = matObject * vec4(vertex,1);"
  "  gl_Position  = matProj * matModel * vertObj;"
  "  vo = vertObj.xyz; nm = normal;"
  "}";

static char const *shaderFragment =
  "uniform highp vec3 lightPos;"
  "uniform highp vec4 color;"

  "varying highp vec3 vo, nm;"

  "void main() {"
  "  highp vec3  L  = normalize(lightPos - vo);"
  "  highp vec3  N  = normalize(nm);"
  "  highp float NL = dot(N,L);"
  "  highp vec4  C  = color*(0.6 + NL*0.4);"  // mix ambient with specular
  "  gl_FragColor   = clamp(C, 0.0, 1.0);"
  "}";
}

void Program::init() {
  if (!doInit)
    return;
  doInit = false;

  addShaderFromSourceCode(QOpenGLShader::Vertex,   shaderVertex);
  addShaderFromSourceCode(QOpenGLShader::Fragment, shaderFragment);

  bindAttributeLocation("vertex", 0);
  bindAttributeLocation("normal", 1);

  link();

  bind();
  locMatProj   = uniformLocation("matProj");
  locMatModel  = uniformLocation("matModel");
  locMatObject = uniformLocation("matObject");
  locLightPos  = uniformLocation("lightPos");
  locColor     = uniformLocation("color");
  release();
}

void Program::set(Camera const& camera) {
  setUniformValue(locMatProj,  camera.matProj);
  setUniformValue(locMatModel, camera.matModel);
  setUniformValue(locLightPos, camera.lightPosRotated);
}

void Program::set(QColor const&color) {
  setUniformValue(locColor, color);
}

void Program::set(QMatrix4x4 const& mat) {
  setUniformValue(locMatObject, mat);
}

//------------------------------------------------------------------------------
}
// eof
