#version 400

in vec2 fragPos;
out vec4 color;

uniform vec3 cameraPos;
#define MAX_LIGHTS 100
uniform vec3 lights[MAX_LIGHTS];
uniform int lightCount;

struct RaycastResult
{
    bool  hit;
    float dist;
    vec3  hitPoint;
    vec3  normal;
    vec3  color;
    float roughness;
};
struct Sphere
{
    vec3  position;
    float radius;
    vec3  color;
    float roughness;
};
struct Plane
{
    vec3 position;
    vec3 normal;
    vec3 color;
    float roughness;
};
struct Ray
{
    vec3  origin;
    vec3  direction;
};
#define MAX_SPHERES 10
uniform int sphereCount;
uniform Sphere spheres[MAX_SPHERES];

#define MAX_PLANES 10
uniform int planeCount;
uniform Plane planes[MAX_PLANES];

RaycastResult SphereRaycast(Sphere sphere, Ray ray)
{
    RaycastResult result = RaycastResult(false, 0, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0), 1);
    RaycastResult result = RaycastResult(false, 0, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0), 1);

    vec3 rayToSphere = ray.origin-sphere.position;

    float a = ray.direction.x*ray.direction.x + ray.direction.y*ray.direction.y + ray.direction.z*ray.direction.z;
    float b = 2*(rayToSphere.x*ray.direction.x + rayToSphere.y*ray.direction.y + rayToSphere.z*ray.direction.z);
    float c = rayToSphere.x*rayToSphere.x + rayToSphere.y*rayToSphere.y + rayToSphere.z*rayToSphere.z - sphere.radius*sphere.radius;

    float t_1 = ( -b + sqrt(b*b - 4*a*c) )/2*a;
    float t_2 = ( -b - sqrt(b*b - 4*a*c) )/2*a;

    if(t_1 < 0 || t_2 < 0 || isnan(t_1) || isnan(t_2))
        return result;
    
    float t = min(t_1, t_2);

    result.hit = true;
    result.hitPoint = ray.origin+ray.direction*t;
    result.dist = distance(ray.origin, result.hitPoint);
    result.normal = normalize(result.hitPoint-sphere.position);
    result.color = sphere.color;
    result.roughness = sphere.roughness;
    result.roughness = sphere.roughness;

    return result;
}
RaycastResult PlaneRaycast(Plane plane, Ray ray)
{
    float numerator = dot(plane.normal, plane.position) - dot(plane.normal, ray.origin);
    float denominator = dot(plane.normal, ray.direction);

    float alpha = numerator/denominator;

    if (alpha > 0 && dot(plane.normal, ray.direction) < 0)
    {
        return RaycastResult(true, alpha, ray.origin+ray.direction*alpha, plane.normal, plane.color, plane.roughness);
        return RaycastResult(true, alpha, ray.origin+ray.direction*alpha, plane.normal, plane.color, plane.roughness);
    }
    return RaycastResult(false, 0, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0), 1);
    return RaycastResult(false, 0, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0), 1);
}
Ray getRay()
{
    return Ray(cameraPos, normalize(vec3(fragPos.xy, 0)-cameraPos));
}
RaycastResult getClosestResult(Ray ray)
{
    RaycastResult closestResult = RaycastResult(false, 0, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0), 1);
    RaycastResult closestResult = RaycastResult(false, 0, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0), 1);
    for(int i = 0; i < sphereCount; i++)
    {
        RaycastResult sphereResult = SphereRaycast(spheres[i], ray);
        if(sphereResult.hit && (!closestResult.hit || sphereResult.dist < closestResult.dist))
        {
            closestResult = sphereResult;
        }
    }
    for(int i = 0; i < planeCount; i++)
    {
        RaycastResult planeResult = PlaneRaycast(planes[i], ray);
        if(planeResult.hit && (!closestResult.hit || planeResult.dist < closestResult.dist))
        {
            closestResult = planeResult;
        }
    }
    return closestResult;
}
RaycastResult getReflectedResult(Ray reflectedRay)
RaycastResult getReflectedResult(Ray reflectedRay)
{
    RaycastResult closestResult = getClosestResult(reflectedRay);
    if(closestResult.hit)
    {
        int hitCount = 0;
        for(int i = 0; i < lightCount; i++)
        {
            vec3 lightDir = lights[i]-closestResult.hitPoint;
            RaycastResult shadowResult = getClosestResult(Ray(closestResult.hitPoint, normalize(lightDir)));
            if(!(shadowResult.hit && shadowResult.dist < length(lightDir) && shadowResult.dist > 0.0005))
            {
                hitCount++;
            }
        }

        float maxDot = 0;
        for(int i = 0; i < lightCount; i++)
        {
            float temp = dot(closestResult.normal, normalize(lights[i]-closestResult.hitPoint));
            maxDot = max(temp, maxDot);
        }
        closestResult.color = closestResult.color * maxDot;
        closestResult.color = closestResult.color * hitCount/lightCount;
    }
    return closestResult;
}
int reflections = 3;
vec3 getColor()
{
    Ray ray = getRay();
    RaycastResult closestResult = getClosestResult(ray);

    if(closestResult.hit)
    {
        int hitCount = 0;
        for(int i = 0; i < lightCount; i++)
        {
            vec3 lightDir = lights[i]-closestResult.hitPoint;
            RaycastResult shadowResult = getClosestResult(Ray(closestResult.hitPoint, normalize(lightDir)));
            if(!(shadowResult.hit && shadowResult.dist < length(lightDir) && shadowResult.dist > 0.0005))
            {
                hitCount++;
            }
        }

        if(closestResult.roughness != 1)
        {
            vec3 reflectionDirection = ray.direction - closestResult.normal * 2*dot(ray.direction, closestResult.normal);
            vec3 reflectionColor = getReflectedResult(Ray(closestResult.hitPoint, normalize(reflectionDirection))).color;

            closestResult.color = closestResult.color*(closestResult.roughness)  + reflectionColor*(1-closestResult.roughness);
        }
        
        float maxDot = 0;
        for(int i = 0; i < lightCount; i++)
        {
            float temp = dot(closestResult.normal, normalize(lights[i]-closestResult.hitPoint));
            maxDot = max(temp, maxDot);
        }
        closestResult.color = closestResult.color * maxDot;
        closestResult.color = closestResult.color * hitCount/lightCount;
    }
    return closestResult.color;
    return closestResult.color;
}

void main()
{
    color = vec4(getColor().xyz, 1);
}