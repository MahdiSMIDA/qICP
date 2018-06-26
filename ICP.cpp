
//Qt
#include <QtGui>
#include<QTime>
#include "ICP.h"
#include "ccIcpDialog.h"
//#include "../utils/cc2sm.h"
//#include "../utils/sm2cc.h"
/* Default constructor */

IcpPlugin::IcpPlugin( QObject *parent )
	: QObject( parent )
    , ccStdPluginInterface( ":/CC/plugin/qICP/info.json" )
	, m_action( nullptr )
{
}

void IcpPlugin::onNewSelection( const ccHObject::Container &selectedEntities )
{
//Enable m_action
    m_action->setEnabled(m_app && m_app->dbRootObject()
    && m_app->dbRootObject()->getChildrenNumber() != 0
    && selectedEntities.size()==2
    && selectedEntities[0]->isA(CC_TYPES::POINT_CLOUD)
    && selectedEntities[1]->isA(CC_TYPES::POINT_CLOUD));
        if (!m_dlg || selectedEntities.size()<2 )
	{
		return;
        }
}

QList<QAction *> IcpPlugin::getActions()
{
        //default action (if it has not been already created, it's the moment to do it)
        if (!m_action) //this is the action triggered by clicking the "Compass" button in the plugin menu
        {
                //here we use the default plugin name, description and icon,
                //but each action can have its own!
                m_action = new QAction(getName(), this);
                m_action->setToolTip(getDescription());
                m_action->setIcon(getIcon());
                //connect appropriate signal
                connect(m_action, &QAction::triggered, this, &IcpPlugin::doAction); //this binds the m_action to the ccCompass::doAction() function
        }

        return QList<QAction *>{ m_action };
}


void IcpPlugin::doAction()
{
    assert(m_app);
    //check valid window
    if (!m_app->getActiveGLWindow())
    {
        m_app->dispToConsole("[Icp] Could not find valid 3D window.", ccMainAppInterface::ERR_CONSOLE_MESSAGE);
       return;
     }
   if (!m_dlg)
    {
        m_dlg = new ccIcpDialog((QWidget*)m_app->getMainWindow());
       this->rootLasFile = m_app->dbRootObject()->getChild(0);
        ccIcpDialog::connect(m_dlg->computeButton, SIGNAL(clicked()), this, SLOT(onCompute()));
        ccIcpDialog::connect(m_dlg->closeButton, SIGNAL(clicked()), this, SLOT(onClose()));

        initializeDrawSettings();
        m_dlg->linkWith(m_app->getActiveGLWindow());
    }

   //start GUI
   //m_app->registerOverlayDialog(m_dlg, Qt::TopRightCorner);
   m_dlg->start();

}


/* Slot on dialog closed */
void IcpPlugin::onClose()
{
    IcpPlugin::stop();
    m_app->removeFromDB(this->m_icpGroup, true);
}

void IcpPlugin::onCompute()
{
    const ccHObject::Container& selectedEntities = m_app->getSelectedEntities();
    ccHObject* cloud =this->rootLasFile->getChild(0) ;
    ccHObject* ent1 = selectedEntities[0];
    ccHObject* ent2 = selectedEntities[1];
    ccPointCloud* cloudSource = ccHObjectCaster::ToPointCloud(ent1);
    ccPointCloud* cloudTarget = ccHObjectCaster::ToPointCloud(ent2);

    //PCLCloud::Ptr pcl_cloudSource = cc2smReader(cloudSource).getAsSM();
    //PCLCloud::Ptr pcl_cloudTarget = cc2smReader(cloudTarget).getAsSM();



}

void IcpPlugin::stop()
{
    //remove overlay GUI
    if (m_dlg)
    {
        m_dlg->stop(true);
        m_app->unregisterOverlayDialog(m_dlg);
    }

   //redraw
    if (m_app->getActiveGLWindow())
    {
        m_app->getActiveGLWindow()->redraw(true, false);
    }
    m_dlg = nullptr;
    ccStdPluginInterface::stop();
}
/* Deconstructor */
IcpPlugin::~IcpPlugin()
{
    if (m_dlg)
        delete m_dlg;
}
void IcpPlugin::initializeDrawSettings(){

    this->m_icpGroup = new ccHObject("Icp plugin Group");
      m_app->addToDB(this->m_icpGroup, false, true, false, false);
}
