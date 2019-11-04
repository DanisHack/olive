#ifndef RENDERBACKEND_H
#define RENDERBACKEND_H

#include "decodercache.h"
#include "node/output/viewer/viewer.h"

class RenderBackend : public QObject
{
  Q_OBJECT
public:
  RenderBackend(QObject* parent = nullptr);
  virtual ~RenderBackend() override;

  Q_DISABLE_COPY_MOVE(RenderBackend)

  bool Init();

  void Close();

  const QString& GetError() const;

  void SetViewerNode(ViewerOutput* viewer_node);

  void SetCacheName(const QString& s);

  bool IsInitiated();

public slots:
  virtual void InvalidateCache(const rational &start_range, const rational &end_range) = 0;

  bool Compile();

  void Decompile();

protected:
  void RegenerateCacheID();

  virtual bool InitInternal() = 0;

  virtual void CloseInternal() = 0;

  virtual bool CompileInternal() = 0;

  virtual void DecompileInternal() = 0;

  DecoderCache decoder_cache_;

  const QVector<QThread*>& threads();

  /**
   * @brief Internal function for generating the cache ID
   */
  virtual bool GenerateCacheIDInternal(QCryptographicHash& hash) = 0;

  void SetError(const QString& error);

  virtual void ViewerNodeChangedEvent(ViewerOutput* node);

  ViewerOutput* viewer_node() const;

  QString cache_name_;
  qint64 cache_time_;
  QString cache_id_;

private:
  /**
   * @brief Internal list of RenderProcessThreads
   */
  QVector<QThread*> threads_;

  /**
   * @brief Internal variable that contains whether the Renderer has started or not
   */
  bool started_;

  /**
   * @brief Internal reference to attached viewer node
   */
  ViewerOutput* viewer_node_;

  /**
   * @brief Error string that can be set in SetError() to handle failures
   */
  QString error_;

  bool compiled_;
};

#endif // RENDERBACKEND_H