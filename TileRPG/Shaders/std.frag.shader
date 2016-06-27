

#version 120

varying vec3 normal;

void main(void)
{
    // Defining The Material Colors
    const vec4 AmbientColor = vec4(0.1, 0.1, 0.45, 1.0);
    const vec4 DiffuseColor = vec4(0.4, 0.4, 0.4, 1.0);

    // TODO: Take these in from gl_LightSource
    // const vec3 ambient = vec3(0.1, 0.1, 0.1);
    const vec3 lightVecNormalized = normalize(vec3(0.0, 0.0, 1.0));

    // Scaling The Input Vector To Length 1
    vec3 normalized_normal = normalize(normal);

    // Calculating The Diffuse Term And Clamping It To [0;1]
    float DiffuseTerm = clamp(dot(normalized_normal, lightVecNormalized), 0.0, 1.0);

    // Calculating The Final Color
    gl_FragColor = AmbientColor + DiffuseColor * DiffuseTerm;

    const vec4 FogColor = vec4(0.0, 0.0, 0.0, 1.0);

    float dist = gl_FragCoord.z / gl_FragCoord.w;
    float fogAmt = clamp(sqrt(dist) / 6, 0.0, 1.0);
    gl_FragColor = mix(gl_FragColor, FogColor, fogAmt);
}
