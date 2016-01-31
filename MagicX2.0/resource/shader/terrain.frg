#version 330 core

uniform sampler2D textureUnit0;
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

in vec3 vVaryingNormal;
in vec3 vVaryingLightDir;

varying vec4 color;
varying vec2 vTex;

out vec4 vFragColor;


void main()
{	
	float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));
	
	vFragColor = diff * diffuseColor;
	
	vFragColor += ambientColor;
	
	vFragColor *= texture2D(textureUnit0, vTex);
	
	vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir), normalize(vVaryingNormal)));
	
	float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
	if (diff != 0)
	{
		float fSpec = pow(spec, 128.0);
		vFragColor.rgb += vec3(fSpec, fSpec, fSpec);
	}
}