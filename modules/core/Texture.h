// Texture class based on OpenCV Mat
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "types.h"

namespace rt {
    // ================================ Texture Class ================================
    /**
     * @brief Texture class
     * @author Dr. Sergey G. Kosov, sergey.kosov@project-10.de
     */
    class CTexture : public Mat {
    public:
        /**
         * @brief Default Constructor
         */
        DllExport CTexture(void) : Mat() {}
        /**
         * @brief Constructor
         * @param fileName The path to the texture file
         */
        DllExport CTexture(const std::string &fileName);
        /**
         * @brief Constructor
         * @param img The texture image
         */
        DllExport CTexture(const Mat &img);

        DllExport CTexture(const CTexture &) = delete;

        DllExport ~CTexture(void) = default;

        DllExport const CTexture &operator=(const CTexture &) = delete;

        /**
         * @brief Returns the texture element with coordinates \b (uv)
         * @param uv The textel coordinates in the texture space, \f$ u,v\in [-1; 1 ] \f$
         * @return The texture elment (color)
         */
        DllExport Vec3f getTexel(const Vec2f &uv) const;


        // INFO:
        // Both methods here are virtual insetad of pure virtual.
        // It's important we keep it this way because if the Texture object doesn't implement this
        // then the normal texture mapping won't work anymore.

        // Idea here is we make the Texture class a base class for all procedural textures.
        // Therefore, allowing them to implement the method below.
        // There are a few benefits to this:
        // * We don't have to change ANY logic in all the other shaders. (In theory, all shaders get this benefit right away).
        // * Generating new procedural textures becomes very easy and simple.
        // ** Simply create a new class, make it derive from CTexture, and implement the two methods, and it works like a charm.
        DllExport virtual Vec3f get3DTexel(const Vec3f &ray);


        // This method should be implemented by all procedural textures and always return true in those cases.
        // Simple and effective way of detecting procedural textures.
        DllExport virtual bool isProcedural();



    };

    using ptr_texture_t = std::shared_ptr<CTexture>;
}
