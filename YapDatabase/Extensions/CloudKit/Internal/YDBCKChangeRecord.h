#import <Foundation/Foundation.h>
#import <CloudKit/CloudKit.h>


@interface YDBCKChangeRecord : NSObject <NSCoding, NSCopying>

- (instancetype)initWithRecord:(CKRecord *)record;

@property (nonatomic, strong, readwrite) CKRecord *record;
@property (nonatomic, assign, readwrite) BOOL canStoreOnlyChangedKeys;

@property (nonatomic, strong, readonly) CKRecordID *recordID;
@property (nonatomic, strong, readonly) NSArray *changedKeys;

@property (nonatomic, readonly) NSSet *changedKeysSet;

@end
