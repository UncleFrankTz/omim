#pragma once

#include "qt/draw_widget.hpp"

#include "storage/index.hpp"

#include "platform/location.hpp"
#include "platform/location_service.hpp"

#include "std/array.hpp"
#include "std/unique_ptr.hpp"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

class Framework;
class QDockWidget;
class QLabel;
class QPushButton;
class QToolButton;
class TrafficMode;

namespace search { class Result; }

namespace qt
{
class MainWindow : public QMainWindow, location::LocationObserver
{
  QAction * m_pMyPositionAction;
  QAction * m_pCreateFeatureAction;
  QAction * m_selectionMode;
  QAction * m_clearSelection;
  QAction * m_pSearchAction;
  QAction * m_trafficEnableAction;
  QAction * m_saveTrafficSampleAction;
  QAction * m_quitTrafficModeAction;
  QToolButton * m_routePointsToolButton;
  QAction * m_selectStartRoutePoint;
  QAction * m_selectFinishRoutePoint;
  QAction * m_selectIntermediateRoutePoint;
#ifdef BUILD_DESIGNER
  QString const m_mapcssFilePath;
  QAction * m_pBuildStyleAction;
  QAction * m_pRecalculateGeomIndex;
  QAction * m_pDrawDebugRectAction;
  QAction * m_pGetStatisticsAction;
  QAction * m_pRunTestsAction;
#endif // BUILD_DESIGNER
  DrawWidget * m_pDrawWidget;
    
  // TODO(mgsergio): Make indexing more informative.
  array<QDockWidget *, 2> m_Docks;

  QPushButton * m_downloadButton;
  QPushButton * m_retryButton;
  QLabel * m_downloadingStatusLabel;
  storage::TCountryId m_lastCountry;

  unique_ptr<location::LocationService> const m_locationService;

  // This object is managed by Qt memory system.
  TrafficMode * m_trafficMode = nullptr;

  Q_OBJECT

public:
  MainWindow(Framework & framework, bool apiOpenGLES3, QString const & mapcssFilePath = QString());

Q_OBJECT

  static void SetDefaultSurfaceFormat(bool apiOpenGLES3);

protected:
  string GetIniFile();

  void LocationStateModeChanged(location::EMyPositionMode mode);

protected:
  void CreatePanelImpl(size_t i, Qt::DockWidgetArea area, QString const & name,
                       QKeySequence const & hotkey, char const * slot);
  void CreateNavigationBar();
  void CreateSearchBarAndPanel();
  void CreateCountryStatusControls();

  void CreateTrafficPanel(string const & dataFilePath, string const & sampleFilePath);
  void DestroyTrafficPanel();

#if defined(Q_WS_WIN)
  /// to handle menu messages
  virtual bool winEvent(MSG * msg, long * result);
#endif

  virtual void closeEvent(QCloseEvent * e);

protected Q_SLOTS:
#ifndef NO_DOWNLOADER
  void ShowUpdateDialog();
#endif // NO_DOWNLOADER

  void OnPreferences();
  void OnAbout();
  void OnMyPosition();
  void OnCreateFeatureClicked();
  void OnSearchButtonClicked();
  void OnLoginMenuItem();
  void OnUploadEditsMenuItem();

  void OnBeforeEngineCreation();

  void OnDownloadClicked();
  void OnRetryDownloadClicked();

  void OnSwitchSelectionMode();
  void OnClearSelection();

  void OnTrafficEnabled();
  void OnOpenTrafficSample();
  void OnSaveTrafficSample();
  void OnQuitTrafficMode();

  void OnStartPointSelected();
  void OnFinishPointSelected();
  void OnIntermediatePointSelected();
  void OnFollowRoute();
  void OnClearRoute();
    
#ifdef BUILD_DESIGNER
    void OnBuildStyle();
    void OnRecalculateGeomIndex();
    void OnDebugStyle();
    void OnGetStatistics();
    void OnRunTests();
#endif // BUILD_DESIGNER
};
}
