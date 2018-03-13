#ifndef _SE_SCENE_CULLER_H_
#define _SE_SCENE_CULLER_H_

namespace se
{
    class ICuller
    {
    public:
        virtual ~ICuller(){}
        virtual void SetFrustum(const CFrustum &) = 0;
        virtual void IsCull(const CAABBox &) = 0;
    };
}

#endif
