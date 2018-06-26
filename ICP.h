

//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: IcpPlugin                          #
//#                                                                        #
//##########################################################################
#ifndef Q_ICP_PLUGIN_HEADER
#define Q_ICP_PLUGIN_HEADER 

#include "ccMainAppInterface.h"
#include "ccStdPluginInterface.h"
#include "ccIcpDialog.h"
#include "ccLog.h"

class IcpPlugin : public QObject, public ccStdPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(ccStdPluginInterface)
    Q_PLUGIN_METADATA(IID "cccorp.cloudcompare.plugin.qICP" FILE "info.json")

public:
    explicit IcpPlugin( QObject *parent = nullptr );
    
     ~IcpPlugin();
    // inherited from ccStdPluginInterface
    virtual void onNewSelection( const ccHObject::Container &selectedEntities ) override;
    virtual QList<QAction *> getActions() override;
    
    virtual void stop() override;
    
    //Icp UI
    ccIcpDialog* m_dlg = nullptr;
    
    //Logger
    Log* logger = nullptr;

private:
    //ccPointCloud* cloudSource ;
    //ccPointCloud* cloudTarget :
    // DB Tree icp group
	ccHObject* m_icpGroup = nullptr;
    ccHObject* rootLasFile = nullptr;
    void doAction();
  
    void initializeDrawSettings();
    QMainWindow* m_main_window = nullptr;
    QAction* m_action;
private slots:
    void onCompute();
    void onClose();
};

#endif
