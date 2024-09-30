#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "Ogre.h"
#include "OgreRTShaderSystem.h"

#include "OgreTrays.h"
#include <OgreCameraMan.h>
#include <iostream>
#include <memory>

namespace ob = OgreBites;

class PointSpriteTest : public ob::ApplicationContext, public ob::InputListener
{
public:
    PointSpriteTest()
      : ob::ApplicationContext("PointSpriteTest")

    {
    }

    void setup();

    bool keyPressed(OgreBites::KeyboardEvent const& evt) override { return mCameraMan->keyPressed(evt); }

    void frameRendered(Ogre::FrameEvent const& evt) override { mCameraMan->frameRendered(evt); }

    bool keyReleased(OgreBites::KeyboardEvent const& evt) override { return mCameraMan->keyReleased(evt); }

    bool mouseMoved(OgreBites::MouseMotionEvent const& evt) override { return mCameraMan->mouseMoved(evt); }

    bool mousePressed(OgreBites::MouseButtonEvent const& evt) override { return mCameraMan->mousePressed(evt); }

    bool mouseReleased(OgreBites::MouseButtonEvent const& evt) override { return mCameraMan->mouseReleased(evt); }

private:
    std::unique_ptr<OgreBites::CameraMan> mCameraMan;
};

void PointSpriteTest::setup()
{
    // OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    // OgreBites::TextBox*     t = mTrayMgr->OgreBites::TrayManager::createTextBox(
    //    OgreBites::TrayLocation::TL_LEFT, "MyTextBox", "TextBox", 120, 100);
    // do not forget to call the base first
    ob::ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    auto root = getRoot();

    // Needed to have the textures load properly
    root->loadPlugin("Codec_STBI");

    auto scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    auto& shadergen = Ogre::RTShader::ShaderGenerator::getSingleton();
    shadergen.addSceneManager(scnMgr);

    scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    auto myNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    auto mySet = scnMgr->createBillboardSet("mySet");

    myNode->attachObject(mySet);
    mySet->setMaterialName("Examples/Flare");
    for (size_t i = 0; i < 1000; ++i)
    {
        auto myBillboard = mySet->createBillboard({Ogre::Math::SymmetricRandom() * 2500,
                                                   Ogre::Math::SymmetricRandom() * 2500,
                                                   Ogre::Math::SymmetricRandom() * 2500});
    }

    /*
    auto mat = Ogre::MaterialManager::getSingleton().create("spriteTest1", "General");
    auto pass = mat->getTechnique(0)->getPass(0);
    pass->setPointSpritesEnabled(true);
    pass->createTextureUnitState("flare_alpha.dds");
    pass->setLightingEnabled(false);
    pass->setDepthWriteEnabled(false);
    pass->setSceneBlending(Ogre::SBT_ADD);
    pass->setPointAttenuation(true);
    pass->setPointSize(12);
    pass->setVertexColourTracking(Ogre::TVC_DIFFUSE);

    {
        auto man = scnMgr->createManualObject("man");
        man->begin("spriteTest1", Ogre::RenderOperation::OT_POINT_LIST);

        for (size_t i = 0; i < 1000; ++i)
        {
            man->position(Ogre::Math::SymmetricRandom() * 500,
                          Ogre::Math::SymmetricRandom() * 500,
                          Ogre::Math::SymmetricRandom() * 500);
            man->colour(Ogre::Math::RangeRandom(0.5f, 1.0f),
                        Ogre::Math::RangeRandom(0.5f, 1.0f),
                        Ogre::Math::RangeRandom(0.5f, 1.0f));
        }

        man->end();
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(man);
    }

    {
        Ogre::ManualObject* man = scnMgr->createManualObject("test");
        man->begin("Examples/OgreLogo", Ogre::RenderOperation::OT_TRIANGLE_LIST);

        man->position(-20, 20, 20);
        man->normal(0, 0, 1);
        man->textureCoord(0, 0);

        man->position(-20, -20, 20);
        man->normal(0, 0, 1);
        man->textureCoord(0, 1);

        man->position(20, -20, 20);
        man->normal(0, 0, 1);
        man->textureCoord(1, 1);

        man->position(20, 20, 20);
        man->normal(0, 0, 1);
        man->textureCoord(1, 0);
        man->quad(0, 1, 2, 3);
        man->end();
        scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(man);
    }
    */
    auto camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 1000);

    auto cam = scnMgr->createCamera("myCam");
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_PARENT);
    cam->setNearClipDistance(0.5);
    camNode->attachObject(cam);
    mCameraMan = std::make_unique<OgreBites::CameraMan>(camNode);
    getRenderWindow()->addViewport(cam);
    setWindowGrab();
}

int main(int argc, char** argv)

try
{
    PointSpriteTest app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
catch (const std::exception& e)
{
    std::cerr << "Error occurred during execution: " << e.what() << '\n';
    return 1;
}
