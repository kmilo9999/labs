#version 330 core

uniform mat4 model, view, projection;

// Light properties
const vec3 WorldSpace_lightPos = vec3(2, 2, 2); // world-space light position
const vec3 testCamPos=vec3(0, 0, 0);
uniform vec3 lightColor;
uniform float lightIntensity;

// Attenuation Properties
uniform float attQuadratic;
uniform float attLinear;
uniform float attConstant;

// Material properties
uniform vec3 color;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;
uniform float shininess;

uniform vec3 CameraSpace_position;

in vec3 Normal;
in vec3 FragPos;
in vec3 viewPos;

out vec3 fragColor;

void main(){




    vec3 lightDir = WorldSpace_lightPos - FragPos;
    vec3 lightDirN = normalize(lightDir);
    float NdotL = max(dot(normalize(Normal), lightDirN), 0.0);


    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDirN, normalize(Normal));
    float EdotR = pow(max(dot(viewDir, normalize(reflectDir)), 0.0), shininess);

    vec3 ambient = ambientIntensity * color;

    float Attenuation = lightIntensity * min(1 / (attConstant + attLinear * length(lightDir) + attQuadratic * pow(length(lightDir),2)), 1);

    vec3 diff = color * lightColor * diffuseIntensity * NdotL;
    diff *= Attenuation;
    vec3 spec = color * lightColor * specularIntensity * EdotR;
    spec *= Attenuation;



    fragColor = ambient +diff +spec;
}
