#version 330 core

in vec3 Normal;
in vec3 fragPos;

uniform vec3 color;
out vec4 FragColor;

uniform vec3 viewPos;

void main() {
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    vec3 normal = normalize(Normal);

    // Ambient
    vec3 ambient = 0.2 * color;
    
    // Diffuse 
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec;

    // Final
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
