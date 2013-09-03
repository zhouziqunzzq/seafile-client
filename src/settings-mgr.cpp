#include "seafile-applet.h"
#include "ui/tray-icon.h"
#include "settings-mgr.h"

#include "rpc/rpc-request.h"

SettingsManager::SettingsManager()
    : auto_sync_(true)
{
}

void SettingsManager::setAutoSync(bool auto_sync)
{
    SeafileRpcRequest *req = new SeafileRpcRequest();
    connect(req, SIGNAL(setAutoSyncSignal(bool, bool)),
            this, SLOT(onSetAutoSyncFinished(bool, bool)));

    req->setAutoSync(auto_sync);
}

void SettingsManager::onSetAutoSyncFinished(bool auto_sync, bool result)
{
    if (result) {
        qDebug("%s auto sync success", auto_sync ? "enable" : "disable");
        auto_sync_ = auto_sync;
        seafApplet->trayIcon()->setState(
            auto_sync
            ? SeafileTrayIcon::STATE_DAEMON_UP
            : SeafileTrayIcon::STATE_DAEMON_AUTOSYNC_DISABLED);
    }
}
