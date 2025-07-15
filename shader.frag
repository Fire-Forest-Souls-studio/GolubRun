// blur_black_fade2.frag
// GLSL 1.20 (SFML)

uniform sampler2D texture;
uniform vec2     resolution;      // размер текстуры в пикселях
uniform float    threshold;       // яркость ≤ threshold = «чёрный»
uniform int      radius;          // радиус сбора соседей для blur
uniform float    fadeInner;       // расстояние (в пикселях) от цветного, где fade=1
uniform float    fadeOuter;       // расстояние, где fade=0 (должно > fadeInner)

// яркость пикселя
float brightness(vec3 c) {
    return dot(c, vec3(0.299, 0.587, 0.114));
}

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec3 center = texture2D(texture, uv).rgb;

    // если пиксель цветной — рисуем как есть
    if (brightness(center) > threshold) {
        gl_FragColor = vec4(center, 1.0);
        return;
    }

    // переводим radius, fadeInner/Outer в UV-координаты
    vec2 px = 1.0 / resolution;
    float innerUV = fadeInner * length(px);
    float outerUV = fadeOuter * length(px);

    // суммируем цвета и ищем минимальную дистанцию до любого цветного пикселя
    vec3 sumColor = vec3(0.0);
    float sumWeight = 0.0;
    float minDist = outerUV; // начнём с «максимальной» (гаснет за границей)

    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            vec2 offset = vec2(dx, dy) * px;
            vec2 sampleUV = uv + offset;
            vec3 sample = texture2D(texture, sampleUV).rgb;
            float b = brightness(sample);
            if (b > threshold) {
                // накопление для blur
                float d = length(offset);
                float w = 1.0 / (d + 1.0); // или exp(-d*0.3)
                sumColor += sample * w;
                sumWeight += w;
                // отслеживаем ближайший цвет
                minDist = min(minDist, d);
            }
        }
    }

    // если цветных пикселей рядом нет — отрисуем чёрный
    if (sumWeight == 0.0) {
        gl_FragColor = vec4(0.0);
        return;
    }

    // усреднённый цвет размытия
    vec3 blurred = sumColor / sumWeight;

    // вычисляем fade-параметр [0..1]
    float fade = clamp( (outerUV - minDist) / (outerUV - innerUV), 0.0, 1.0 );

    // итоговый цвет — размытие, приглушённое к чёрному
    vec3 outColor = blurred * fade;
    gl_FragColor = vec4(outColor, 1.0);
}
