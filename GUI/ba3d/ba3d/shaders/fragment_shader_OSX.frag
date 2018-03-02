uniform highp vec3 lightPos;
uniform highp vec4 color;

varying highp vec3 vo, nm;

void main() {
  highp vec3  L  = normalize(lightPos - vo);
  highp vec3  N  = normalize(nm);
  highp float NL = dot(N,L);
  highp vec4  C  = color*(0.6 + NL*0.4);  // mix ambient with specular
  gl_FragColor   = clamp(C, 0.0, 1.0);
}
