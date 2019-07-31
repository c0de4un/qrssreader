/**
* Copyright © Denis Z. (code4un@yandex.ru) All rights reserved.
* Authors: Denis Z. (code4un@yandex.ru)
* All rights reserved.
* Language: C++
* License: see LICENSE
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
* IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef Q_RSS_READER_CHANNEL_MODEL_HPP
#define Q_RSS_READER_CHANNEL_MODEL_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include QAbstractItemModel
#ifndef QABSTRACTITEMMODEL_H
#include <QAbstractItemModel>
#endif // !QABSTRACTITEMMODEL_H

// Include QObject
#ifndef QOBJECT_H
#include <QObject>
#endif // !QOBJECT_H

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// ChannelModel
// ===========================================================

/**
  * ChannelModel - tree-model for RSS Channels.
  *
  * @brief
  * Structure:
  *  - Channel:
  *    - Image (Logo, Icon);
  *    - Name (Title);
  *    - Url;
  *    - Items (News):
  *      -
  *
  * @version 0.1
  * @since 21.07.2019
  * @authors Denis Z. (code4un@yandex.ru)
**/
class ChannelModel : public QAbstractItemModel
{

    // -----------------------------------------------------------

    // ===========================================================
    // QT MACROS
    // ===========================================================

    Q_OBJECT

    // -----------------------------------------------------------

private:

    // -----------------------------------------------------------

    // -----------------------------------------------------------

public:

    // -----------------------------------------------------------

    /**
      * ChannelModel constructor.
      *
      * @param qParent - Parent-Object. default is null.
      * @throws - no exceptions.
    **/
    explicit ChannelModel( QObject *const qParent = nullptr ) noexcept;

    // -----------------------------------------------------------

}; /// ChannelModel

// -----------------------------------------------------------

#endif // !Q_RSS_READER_CHANNEL_MODEL_HPP
