#version 410
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vPosition;
out vec4 fragColor;

uniform sampler2D diffuse;
uniform vec3 lightColour; //for diffuse
uniform vec3 ambientColour;
uniform vec3 ambientColourScale;
uniform vec3 lightDirection;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform float attenuation;
uniform float specPower;

uniform float coneAngle;

vec4 SpotLight(vec3 lightDir)
{
    float distance = distance(lightPos, vPosition);
    vec3 vDir = normalize(vPosition - lightPos);
    float angle = degrees(acos(dot(-vDir, normalize(lightDir))));
    float attenuationVal = attenuation;
    float diff = 1 - cos(coneAngle);
    float factor = clamp((angle - cos(coneAngle))/diff, 0, 1);
    if (angle > coneAngle)
    {
        attenuationVal = 0;
    }

    return vec4(lightColour, 1.0f) * (1/distance) * attenuationVal;

    /*
    float distance = distance(lightPos, vPosition);
    vec3 vDir = normalize(vPosition - lightPos);
    float cosine = dot(lightDir, vDir);
    float diff = 1 - coneCosine;
    float factor = clamp((cosine - coneCosine)/diff, 0, 1);
    if (cosine > coneCosine)
    {
        return vec4(lightColour, 1.0f) * (factor/distance);
    }
    */      

    //return vec4(0,0,0,0); //black
}

vec4 DiffuseLight(vec3 lightDir)
{
    float d = max(0, dot(normalize(vNormal), lightDir));

    return vec4(d,d,d,1);    
}

vec4 SpecularLight(vec3 lightDir)
{
    float d = max(0, dot(normalize(vNormal), lightDir));

    //specular calculations
    vec3 E = normalize(cameraPos - vPosition); //direction from vertex to camera
    vec3 R = reflect(-lightDir, vNormal);
    float s = max(0, dot(E,R));
    s = pow(s, specPower); 
    
    return s * vec4(1,1,1,1);
}


vec4 SpecularDirectionalLight(vec3 lightDir)
{
   
    float d = max(0, dot(normalize(vNormal), lightDir));

    //specular calculations
    vec3 E = normalize(cameraPos - vPosition); //direction from vertex to camera
    vec3 R = reflect(-lightDir, vNormal);
    float s = max(0, dot(E,R));
    s = pow(s, specPower);

    vec3 Specular = s * vec3(1,1,1);
    vec3 Diffuse = d * vec3(1,1,1);

    return vec4(Specular + Diffuse, 1);
}

void main() 
{ 
    vec3 pointLightDir = normalize(lightPos - vPosition);

    vec4 Ambient = vec4(ambientColour * ambientColourScale, 1);
    vec4 Diffuse = DiffuseLight(pointLightDir);
    vec4 Specular = SpecularLight(pointLightDir);
    vec4 SpotLight = SpotLight(pointLightDir);

    fragColor = texture(diffuse, vTexCoord) * SpotLight + Specular + Ambient;
}

