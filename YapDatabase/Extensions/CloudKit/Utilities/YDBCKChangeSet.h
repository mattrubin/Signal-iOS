#import <Foundation/Foundation.h>

/**
 * A change-set represents the set of changes that will be given to a CKModifyRecordsOperation.
 *
 * A change-set is automatically generated by a readWriteTransaction
 * that makes one or more changes that result in modifications that need to be pushed to the CloudKit server.
 * 
 * Changes are grouped by databaseIdentifier.
 * So if a single readWriteTransaction makes several modifications that span multiple databaseIdentifiers,
 * then the transaction will result in multiple generated change-sets.
 *
 * You are free to inspect the change-set, however, it is not possible to modify it.
**/
@interface YDBCKChangeSet : NSObject

@property (nonatomic, strong, readonly) NSString *databaseIdentifier;

@property (nonatomic, readonly) NSArray *recordIDsToDelete;    // Array of CKRecordID's for CKModifyRecordsOperation
@property (nonatomic, readonly) NSArray *recordsToSave_noCopy; // Array of CKRecord's for CKModifyRecordsOperation

@end
