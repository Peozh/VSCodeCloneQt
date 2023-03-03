#include "myplaintextedit.h"

MyPlainTextEdit::MyPlainTextEdit(QWidget *parent)
    : QPlainTextEdit{parent}
{
    this->p_process = new QProcess (this);
//    p_process-> start ("powershell.exe");
//    p_process-> write("bloc-notes \ n");
//    p_process-> waitForBytesWritten ();
    connect(this->p_process, &QProcess::readyReadStandardOutput, [this](){
        QByteArray data = this->p_process->readAllStandardOutput(); //StandardOutput();
//        if (data[0].isSpace()) data.remove(0, 1);
//        if (data.back().isSpace()) data.remove(data.size()-1, 1);
        auto trimmedData = data.trimmed();
        qDebug() << "before print position : " << this->textCursor().position(); /////////////////
        {
            std::lock_guard<std::mutex> lg(mtx_qtInput);
//            this->insertPlainText(QString::fromLocal8Bit(data));
            this->appendPlainText(QString::fromLocal8Bit(trimmedData + ' '));

            auto cursor = this->textCursor();
            cursor.movePosition(QTextCursor::End);
            this->setTextCursor(cursor);
            if (isClear) this->clearAllQtInput();
            this->startPosition = this->textCursor().position();
            this->isDoneCout = true;
        }
        qDebug() << "print complete position : " << startPosition; /////////////////
        this->document()->clearUndoRedoStacks();
        this->ensureCursorVisible();
    });
    connect(this->p_process, &QProcess::readyReadStandardError, [this](){
        QByteArray data = this->p_process->readAllStandardError();
        auto trimmedData = data.trimmed();
        {
            std::lock_guard<std::mutex> lg(mtx_qtInput);
            this->appendPlainText(QString::fromLocal8Bit(trimmedData + ' '));

            auto cursor = this->textCursor();
            cursor.movePosition(QTextCursor::End);
            this->setTextCursor(cursor);
            this->startPosition = this->textCursor().position();
            this->isDoneError = true;
        }
        qDebug() << "print complete position : " << startPosition; ///////////////
        this->document()->clearUndoRedoStacks();
        this->ensureCursorVisible();
    });

    auto cursor = this->textCursor();
    auto blockFormat = cursor.blockFormat();
    blockFormat.setLineHeight(200, QTextBlockFormat::ProportionalHeight);
    cursor.setBlockFormat(blockFormat);
    this->setTextCursor(cursor);

    cursor = this->textCursor();
    cursor.clearSelection();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(blockFormat);
    this->setTextCursor(cursor);


    bool opened = openPowershell();

//    this->setStyleSheet("QPlainTextEdit { background-color: #222222; color: #eeeeee; font-family: "Consolas"; }");
}

MyPlainTextEdit::~MyPlainTextEdit()
{
    auto pid = p_process->processId();
    if (pid == 0) return;
    QByteArray script = R"(function Kill-Processes ($ParentProcessId) {
        $filter = "parentprocessid = '$($ParentProcessId)'"
        Get-CIMInstance -ClassName win32_process -filter $filter | Foreach-Object {
            $_
            if ($_.ParentProcessId -ne $_.ProcessId) {
                Kill-Processes $_.ProcessId
            }
        }
        taskkill.exe /PID $_.ProcessId /F
    } )";
    QByteArray command = "Kill-Processes " + QByteArray::number(p_process->processId());
    qDebug() << command;
    QProcess terminator;
    terminator.start("powershell.exe", QStringList() << "-Command" << script << "\n\n" << command);
    terminator.waitForFinished();
//    this->p_process->write("exit\n");
//    this->p_process->terminate();
//    this->p_process->kill();
//    this->p_process->kill();
//    this->p_process->kill();
//    this->p_process->waitForFinished();
//    this->p_process->write("exit\n");
//    this->p_process->waitForBytesWritten (200);
//    this->p_process->write("exit\n");
//    this->p_process->waitForBytesWritten(200);
//    this->p_process->closeWriteChannel();
//    if (!this->p_process->waitForFinished(200)) this->p_process->terminate(); // wait 3000 ms and terminate.
//    QProcess terminator;
//    terminator.execute("powershell.exe", QStringList() << "-command" << script);
}

bool MyPlainTextEdit::openPowershell()
{
    p_process->start("powershell.exe", QStringList() << "-NoExit" << "-Command" << "& {Set-Location $env:systemroot}" );
//    p_process->start("powershell.exe", QStringList() << "-NoExit" << "-Command" << "try { . \"C:\\Users\\LJS\\AppData\\Local\\Programs\\Microsoft VS Code\\resources\\app\\out\\vs\\workbench\\contrib\\terminal\\browser\\media\\shellIntegration.ps1\" } catch {}");
    if (!p_process->waitForStarted()) return false;
    return true;
}

void MyPlainTextEdit::clearCurrentQtInput()
{
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::End);

    int endPosition = cursor.position();
    int currentInputLength = endPosition - startPosition;
    qDebug() << "end position : " << endPosition;
    qDebug() << "start position : " << startPosition;
    if (currentInputLength < 0) return;

    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, currentInputLength);
    cursor.removeSelectedText();
    this->setTextCursor(cursor);
}

QString MyPlainTextEdit::getCurrentQtInput()
{
    QString data = this->toPlainText();
    return data.right(data.size() - startPosition);
    QStringList lines = data.split('\n');
    QStringList lastCommand = lines.back().split("> ");
    return lastCommand.back();
}

void MyPlainTextEdit::clearAllQtInput()
{
    auto cursor = this->textCursor();
    cursor.movePosition(QTextCursor::Start);
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.removeSelectedText();
    this->setTextCursor(cursor);
    cursor.movePosition(QTextCursor::End);
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.deletePreviousChar();
    this->setTextCursor(cursor);
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);
    isClear = false;
    this->startPosition = this->textCursor().position();
}

void MyPlainTextEdit::mousePressEvent(QMouseEvent *e)
{
    std::lock_guard<std::mutex> lg(mtx_qtInput);
    if (!isDoneCout && !isDoneError) return;
    if (e->buttons() == Qt::RightButton)
    {
        auto cursor = this->textCursor();
        if (cursor.position() < startPosition) { cursor.setPosition(startPosition); this->setTextCursor(cursor); }
        QString clipText = "";
        if (p_clipboard != nullptr) clipText = p_clipboard->text();
        this->insertPlainText(clipText.toLocal8Bit());
        return;
    }
    else QPlainTextEdit::mousePressEvent(e);
}

void MyPlainTextEdit::keyPressEvent(QKeyEvent *e)
{
    std::lock_guard<std::mutex> lg(mtx_qtInput);
    qDebug() << e->key();
    if (!isDoneCout && !isDoneError) return;
    auto cursor = this->textCursor();

    if (e->modifiers() & Qt::ShiftModifier) { QPlainTextEdit::keyPressEvent(e); return; }
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->key() == Qt::Key_V) { if (cursor.position() < startPosition) { cursor.setPosition(startPosition); this->setTextCursor(cursor); } }
        QPlainTextEdit::keyPressEvent(e); return;
    }

    if (cursor.position() < startPosition) { cursor.setPosition(startPosition); this->setTextCursor(cursor); }
    if (e->key() == Qt::Key_Return)
    {
        cacheIdx = -1;

        QString text = getCurrentQtInput(); /////////////
        commandCache.push_front(text);
        if (commandCache.size() > 20) commandCache.pop_back();
        text = text.trimmed();
        if (text == "clear") { isClear = true; this->clear(); }
        text += '\n';
//        this->clearCurrentQtInput();
        p_process->write(text.toLocal8Bit());
//        p_process->waitForBytesWritten();
        this->isDoneCout = false;
        this->isDoneError = false;
    }
    else if (e->key() == Qt::Key_Tab)
    {
//        QString text = getCurrentQtInput();
//        text += '\t';
//        p_process->write(text.toLocal8Bit());

//        this->isDoneCout = false;
//        this->isDoneError = false;
    }
    else if (e->key() == Qt::Key_Up && !(e->modifiers() & Qt::ShiftModifier))
    {
        if (commandCache.empty()) return;
        if (cacheIdx+1 >= commandCache.size()) return;
        ++cacheIdx;
        QString text = commandCache[cacheIdx];

        this->clearCurrentQtInput();
        this->insertPlainText(QString::fromLocal8Bit(text.toUtf8()));
    }
    else if (e->key() == Qt::Key_Down && !(e->modifiers() & Qt::ShiftModifier))
    {
        if (cacheIdx-1 < 0) return;
        --cacheIdx;
        QString text = commandCache[cacheIdx];
        this->clearCurrentQtInput();
        this->insertPlainText(QString::fromLocal8Bit(text.toUtf8()));
    }
    else if (e->key() == Qt::Key_Left)
    {
        cursor = this->textCursor();
        if (cursor.position() > startPosition) QPlainTextEdit::keyPressEvent(e);
    }
    else if (e->key() == Qt::Key_Backspace)
    {
        cursor = this->textCursor();
        if (cursor.position() > startPosition) QPlainTextEdit::keyPressEvent(e);
    }
    else QPlainTextEdit::keyPressEvent(e);

    if (!isDoneCout && !isDoneError) return;
//    cursor = this->textCursor();
//    if (cursor.position() < startPosition) { cursor.setPosition(startPosition); this->setTextCursor(cursor); }
//    this->ensureCursorVisible();
}

void MyPlainTextEdit::paintEvent(QPaintEvent* event)
{
    QPlainTextEdit::paintEvent(event);
    QPainter p(this->viewport());
    p.fillRect(cursorRect(), QBrush(Qt::white));
}

void MyPlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
//    QMenu *menu = createStandardContextMenu();
//    menu->addAction(tr("My Menu Item"));
//    //...
//    menu->exec(event->globalPos());
//    delete menu;
}

void MyPlainTextEdit::connectClipboard(QClipboard *clipboard)
{
    this->p_clipboard = clipboard;
}

