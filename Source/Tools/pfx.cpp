#include "pfx.h"
#include "particle_fx_manager.h"

using namespace vis;

PFX* PFX::inst=NULL;


PFX::PFX()
{
    // Initial data for hmi
    pfx=NULL;
    emitter_index_selected=1;
    loadParticleEffect("acft_smoke1.pfx");
}


void PFX::loadParticleEffect(std::string filename)
{
    if (pfx!=NULL)
    {
      delete pfx;
    }

    partres_=vis::load_pfx_resource(filename.c_str());

    vis::Particle_fx* particleEff=new Particle_fx(partres_);
    pfx=particleEff;
}

void PFX::saveParticleEffect(std::string filename)
{

}

vis::Particle_fx_resource* PFX::resource()
{
    vis::Particle_fx_resource* ret=partres_.get();
    return (ret);
}


vis::Particle_fx::Emitter* PFX::getLoadedEmitter(int index)
{
    if (index<pfx->num_emitters) {
        return (&pfx->emitters[index]);
    }
    else
    {
        return NULL;
    }

}

// Not so sure this will work
vis::Particle_affector* PFX::getLoadedAffector(int index,int affectorIndex)
{
    if (index<pfx->num_emitters) {
        return &pfx->emitters[index].affectors[affectorIndex];
    }
    else
    {
        return NULL;
    }
}


PFX* PFX::instance(){
    if (inst==NULL) {
        inst=new PFX();
    }
    return inst;
}






