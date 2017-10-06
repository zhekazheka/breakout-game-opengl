#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
    
    // awesome. Split screen
//    if(gl_FragCoord.x < 400)
//        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//    else
//        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
