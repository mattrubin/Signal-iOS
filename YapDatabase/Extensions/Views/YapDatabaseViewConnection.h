#import <Foundation/Foundation.h>

#import "YapDatabaseExtensionConnection.h"
#import "YapDatabaseViewChange.h"
#import "YapDatabaseViewMappings.h"

@class YapDatabaseView;

/**
 * Welcome to YapDatabase!
 *
 * https://github.com/yaptv/YapDatabase
 *
 * The project wiki has a wealth of documentation if you have any questions.
 * https://github.com/yaptv/YapDatabase/wiki
 *
 * YapDatabaseView is an extension designed to work with YapDatabase.
 * It gives you a persistent sorted "view" of a configurable subset of your data.
 *
 * For the full documentation on Views, please see the related wiki article:
 * https://github.com/yaptv/YapDatabase/wiki/Views
 *
 *
 * As a extension, YapDatabaseViewConnection is automatically created by YapDatabaseConnnection.
 * You can access this object via:
 *
 * [databaseConnection extension:@"myRegisteredViewName"]
 *
 * @see YapDatabaseView
 * @see YapDatabaseViewTransaction
**/
@interface YapDatabaseViewConnection : YapDatabaseExtensionConnection

/**
 * Returns the parent view instance.
**/
@property (nonatomic, strong, readonly) YapDatabaseView *view;

/**
 * Want to easily animate a tableView or collectionView when the view changes?
 * Want an exact list of changes that happend to the view?
 *
 * You're in luck!
 *
 * Here's an overview of how it works:
 *
 * - (void)yapDatabaseModified:(NSNotification *)notification
 * {
 *     // Jump to the most recent commit.
 *     // End & Re-Begin the long-lived transaction atomically.
 *     // Also grab all the notifications for all the commits that I jump.
 *     NSArray *notifications = [roDatabaseConnection beginLongLivedReadTransaction];
 *
 *     // What changed in my tableView?
 *
 *     NSArray *sectionChanges = nil;
 *     NSArray *rowChanges = nil;
 * 
 *     [[databaseConnection extension:@"sales"] getSectionChanges:&sectionChanges
 *                                                     rowChanges:&rowChanges
 *                                               forNotifications:notifications
 *                                                   withMappings:mappings];
 *
 *     if ([sectionChanges count] == 0 && [rowChanges count] == 0)
 *     {
 *         // There aren't any changes that affect our tableView!
 *         return;
 *     }
 *
 *     // Familiar with NSFetchedResultsController?
 *     // Then this should look pretty familiar
 *
 *     [self.tableView beginUpdates];
 *
 *     for (YapDatabaseViewSectionChange *sectionChange in sectionChanges)
 *     {
 *         switch (sectionChange.type)
 *         {
 *             case YapDatabaseViewChangeDelete :
 *             {
 *                 [self.tableView deleteSections:[NSIndexSet indexSetWithIndex:sectionChange.index]
 *                               withRowAnimation:UITableViewRowAnimationAutomatic];
 *                 break;
 *             }
 *             case YapDatabaseViewChangeInsert :
 *             {
 *                 [self.tableView insertSections:[NSIndexSet indexSetWithIndex:sectionChange.index]
 *                               withRowAnimation:UITableViewRowAnimationAutomatic];
 *                 break;
 *             }
 *         }
 *     }
 *     for (YapDatabaseViewRowChange *rowChange in rowChanges)
 *     {
 *         switch (rowChange.type)
 *         {
 *             case YapDatabaseViewChangeDelete :
 *             {
 *                [self.tableView deleteRowsAtIndexPaths:@[ rowChange.indexPath ]
 *                                      withRowAnimation:UITableViewRowAnimationAutomatic];
 *                break;
 *            }
 *            case YapDatabaseViewChangeInsert :
 *            {
 *                [self.tableView insertRowsAtIndexPaths:@[ rowChange.newIndexPath ]
 *                                      withRowAnimation:UITableViewRowAnimationAutomatic];
 *                break;
 *            }
 *            case YapDatabaseViewChangeMove :
 *            {
 *                [self.tableView deleteRowsAtIndexPaths:@[ rowChange.indexPath ]
 *                                      withRowAnimation:UITableViewRowAnimationAutomatic];
 *                [self.tableView insertRowsAtIndexPaths:@[ rowChange.newIndexPath ]
 *                                      withRowAnimation:UITableViewRowAnimationAutomatic];
 *                break;
 *            }
 *            case YapDatabaseViewChangeUpdate :
 *            {
 *                [self.tableView reloadRowsAtIndexPaths:@[ rowChange.indexPath ]
 *                                      withRowAnimation:UITableViewRowAnimationAutomatic];
 *                break;
 *            }
 *        }
 *    }
 *
 *    [self.tableView endUpdates];
 * }
**/
- (void)getSectionChanges:(NSArray **)sectionChangesPtr
               rowChanges:(NSArray **)rowChangesPtr
         forNotifications:(NSArray *)notifications
             withMappings:(YapDatabaseViewMappings *)mappings;

/**
 * A simple YES/NO query to see if the view changed at all, inclusive of all groups.
**/
- (BOOL)hasChangesForNotifications:(NSArray *)notifications;

@end
