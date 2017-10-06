#version 330 core
struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 diffuseTex = texture(material.diffuse, TexCoords).rgb;
    vec3 specularTex = texture(material.specular, TexCoords).rgb;
    
    // ambient color
    vec3 ambient = light.ambient * diffuseTex;
    
    // diffuse color
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseTex;
    
    // specular color
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * specularTex;
    
    vec3 emission = vec3(0.0);
    if(specularTex.r == 0.0)
    {
        emission = texture(material.emission, TexCoords).rgb;
    }
    
    vec3 resultColor = ambient + diffuse + specular;
    FragColor = vec4(resultColor, 1.0);
}
