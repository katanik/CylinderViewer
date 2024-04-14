varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;
uniform highp vec3 color;

void main()
{
    highp vec3 L = normalize(lightPos - vert);
    highp float NL = max(dot(normalize(vertNormal), L), 0.0);
    highp float lightness = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
    highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, (lightness < 0.1 ? 0.1 : 0.0) * NL, 1.0);
    gl_FragColor = vec4(col , 1.0);
}
