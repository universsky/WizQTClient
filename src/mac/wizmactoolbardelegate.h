#ifndef WIZMACTOOLBARDELEGATE_H
#define WIZMACTOOLBARDELEGATE_H

#include <QtGlobal>

#ifdef Q_OS_MAC

#import <AppKit/AppKit.h>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtGui/QAction>

#include "wizmacToolbar.h"



class CWizMacToolBarItem;



#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_6
@protocol NSToolbarDelegate @end
#endif

@interface CWizMacToolBarDelegate : NSObject <NSToolbarDelegate, NSTextFieldDelegate>
{
@public
    NSToolbar *m_toolbar;
    CWizMacToolBar* m_qtToolBar;

    QList<CWizMacToolBarItem *> *items;
}

- (id)initWithToolbar:(NSToolbar*)tb qtToolBar:(CWizMacToolBar*)qtToolBar;
//
- (NSToolbarItem *) toolbar: (NSToolbar *)toolbar itemForItemIdentifier: (NSString *) itemIdent willBeInsertedIntoToolbar:(BOOL) willBeInserted;
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)tb;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)Toolbar;
- (NSArray *)toolbarSelectableItemIdentifiers:(NSToolbar *)Toolbar;
//
- (BOOL) control:(NSControl *)control textShouldEndEditing:(NSText *)fieldEditor;
//

- (void)addActionGroup:(QActionGroup *)actionGroup;
- (void)addAction:(QAction *)action;
- (void)addStandardItem:(CWizMacToolBar::StandardItem)standardItem;
- (void)addSearch:(const QString&)label tooltip:(const QString&)tooltip;

- (CWizMacToolBarItem*) itemFromItemIdentifier: (NSString*)itemIdentifier;
- (NSToolbarItem*) itemIdentifierToItem: (NSString*)itemIdentifier;

- (CWizMacToolBarItem*) itemFromItemIdentifierWithChildren: (NSString*)itemIdentifier;
- (CWizMacToolBarItem*) findItemGroup: (NSString*)itemIdentifier;


- (void) viewSizeChanged:(NSNotification*)notification;
- (IBAction)itemClicked:(id)sender;
@end




class CWizMacToolBarItem : public QObject
{
public:
    virtual NSString* itemIdentifier() const = 0;
    virtual NSToolbarItem* toItem() = 0;
    virtual void trigger() { }
    virtual void onActionChanged()  { }
    //
    virtual bool isGroup() const { return false; }
    virtual int childCount() const { return 0; }
    virtual CWizMacToolBarItem* childItem(int index) const { Q_UNUSED(index); return NULL; }
    virtual int indexOf(CWizMacToolBarItem* item) const { Q_UNUSED(item); return -1; }
    virtual CWizMacToolBarItem* childItemFromItemIdentifier(NSString* itemIdentifier)  { Q_UNUSED(itemIdentifier); return NULL; }
    virtual void childItemTriggerred(CWizMacToolBarItem* itemChild) { Q_UNUSED(itemChild); }
    virtual void setChildItemEnabled(CWizMacToolBarItem* itemChild, bool enabled) { Q_UNUSED(itemChild); Q_UNUSED(enabled); }
};



#endif  //Q_OS_MAC

#endif // WIZMACTOOLBARDELEGATE_H