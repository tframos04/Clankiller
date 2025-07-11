#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Input lighting values
uniform vec3 viewPos;
#define MAX_LIGHTS 4
struct Light {
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
    bool enabled;
    float atten;
};
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;

// Output fragment color
out vec4 finalColor;

// Light calculation function
vec4 ProcessLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedo);

void main()
{
    // Base color from texture or uniform
    vec4 albedo = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
    
    // If alpha is 0, discard pixel
    if (albedo.a == 0.0) discard;

    vec3 viewDir = normalize(viewPos - fragPosition);
    vec4 totalLight = vec4(0.0);

    // Process all active lights
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled)
        {
            totalLight += ProcessLight(lights[i], fragNormal, fragPosition, viewDir, albedo);
        }
    }
    
    // Final color is a combination of ambient and processed lights
    finalColor = (totalLight + ambient)*albedo;
}

vec4 ProcessLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedo)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff*light.color.rgb;
    
    // Specular lighting
    float shininess = 32.0;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec*light.color.rgb;

    return vec4(diffuse + specular, 1.0);
}