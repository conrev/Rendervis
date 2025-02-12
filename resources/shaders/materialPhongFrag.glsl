#version 330

in vec4 vertColor;
in vec2 vertUV;
in vec3 worldPos;
in vec3 worldNormal;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform Material material;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.2f;
    float specularStrength = 1.0f;

    vec4 objectColor = texture2D(material.diffuse, vertUV);
    vec3 ambientLuminance = ambientStrength * lightColor * objectColor.rgb;

    vec3 normalizedNormal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPos);

    vec3 diffuseLuminance = max(dot(normalizedNormal,lightDir),0.0) * lightColor * objectColor.rgb;
    vec3 viewDir = normalize(viewPosition - worldPos);
       
    vec3 reflectDir = reflect(-lightDir, normalizedNormal);
    vec3 specularLuminance = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * lightColor * texture2D(material.specular, vertUV).rgb; 

    FragColor = vec4(ambientLuminance + diffuseLuminance + specularLuminance, 1.0);
}