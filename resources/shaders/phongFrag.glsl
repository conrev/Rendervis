#version 330

in vec4 vertColor;
in vec2 vertUV;
in vec3 worldPos;
in vec3 worldNormal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform sampler2D textureData;

void main()
{
    float ambientStrength = 0.2f;
    float specularStrength = 0.5f;

    vec4 objectColor = texture2D(textureData, vertUV);
    vec3 ambientLuminance = ambientStrength * lightColor * objectColor.rgb;

    vec3 normalizedNormal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPos);

    vec3 diffuseLuminance = max(dot(normalizedNormal,lightDir),0.0) * lightColor * objectColor.rgb;
    vec3 viewDir = normalize(viewPosition - worldPos);
       
    vec3 reflectDir = reflect(-lightDir, normalizedNormal);
    vec3 specularLuminance = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 32) * lightColor; 

    FragColor = vec4(ambientLuminance + diffuseLuminance + specularLuminance, 1.0);
}