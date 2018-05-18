uniform highp vec3 lightPos;
uniform highp vec4 color;
uniform highp float ambient;
uniform highp vec3 eye;

varying highp vec3 vo, nm;

void main() {
    // ambient
    highp vec3 amb_col = ambient * color.rgb;

    // diffuse
    highp vec3  L  = normalize(lightPos - vo);
    highp vec3  N  = normalize(nm);
    highp float NL = 0.6*max(0.0f, dot(N,L));
    highp vec3 diff_col = NL * color.rgb;

    // specular
    float spec = 0.0;
    highp vec3 E = normalize(eye-vo);
    if(NL > 0.0f)
        spec = pow(max(0.0, dot(E, reflect(-L, N))), 5.0f);
    vec3 spec_col = spec * vec3(1.0f, 1.0f, 1.0f);

    highp vec3 tot_col = amb_col + diff_col + spec_col;
    highp vec4 C = vec4(tot_col, color.a);
    gl_FragColor = clamp(C, 0.0, 1.0);
}
