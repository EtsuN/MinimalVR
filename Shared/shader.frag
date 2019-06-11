#version 410 core
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform int transparent;

in vec3 vertNormal;
in vec3 vertPosition; 
in vec2 vertTexture;

out vec4 fragColor;

uniform sampler2D texture_diffuse1;

void main()
{
	if (transparent > 0) {
		fragColor = vec4(objectColor, 0.4);
		return;
	}

	vec3 color = vec3(texture(texture_diffuse1, vertTexture));

	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(vertNormal);
    vec3 lightDir = normalize(lightPos - vertPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - vertPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
	
	//color = (ambient + diffuse + specular) * color;
	//fragColor = vec4(color, 1.0);


	// old codes
    //vec3 color = vertNormal;
    //fragColor = vec4(color, 1.0);
}
