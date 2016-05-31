#ifndef PFX_H
#define PFX_H
#include "particle_fx.h"
#include <memory>
#include <vector>

class PFX
{
public:
    void loadParticleEffect(std::string filename);
    void saveParticleEffect(std::string filename);
    void resetFromResource();
    vis::Particle_fx_resource *resource();

    vis::Particle_fx::Emitter* getLoadedEmitter(int index);
    vis::Particle_affector* getLoadedAffector(int index,int affectorIndex);
    static PFX* instance();

    vis::Particle_fx* pfx;
private:
    PFX();
    std::shared_ptr<vis::Particle_fx_resource> partres_;
    static PFX* inst;
};

#endif // PFX_H
