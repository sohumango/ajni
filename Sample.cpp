#include<string>
#include<vector>
#include "com_test_Test.h"


typedef struct _JNI_POSREC {
    jclass cls;
    jmethodID constructortorID;
    jfieldID nameID;
    jfieldID rollNumberID;
    jfieldID scoresID;
    jfieldID departementID;
    jfieldID totalMarkID;
    jfieldID hasReservationID;
} JNI_POSREC;

/**
*   Return Search class.
*/
struct SearchRecord {
    std::string name;
    int rollNumber;
    int scores[5];
    std::string departement;
    float    totalMark;
    bool   hasReservation;
};

JNI_POSREC * jniPosRec = NULL;

/**
*   Fills the Student Record Details.
*/
void FillStudentRecordDetails(std::vector<SearchRecord*>* searchRecordResult ){
    SearchRecord *pRecord1 = new SearchRecord();
    pRecord1->name = "Ram";
    pRecord1->rollNumber = 1;
    for (int i = 0; i < sizeof(pRecord1->scores)/sizeof(int); i++) {
        int s = i+31;
        pRecord1->scores[i] = s;
        printf("Score :%d ", s);
    }
    printf("\n");
    pRecord1->departement = "Computer Science";
    pRecord1->totalMark = 512.500;
    pRecord1->hasReservation = true;
    searchRecordResult->push_back(pRecord1);

    SearchRecord *pRecord2 = new SearchRecord();
    pRecord2->name = "Raju";
    pRecord2->rollNumber = 2;
    for (int i = 0; i < sizeof(pRecord2->scores)/sizeof(int); i++) {
        int s = i+51;
        pRecord2->scores[i] = s;
        printf("Score :%d ", s);
    }

    pRecord2->departement = "Electronics";
    pRecord2->totalMark = 572.25;
    pRecord2->hasReservation = false;
    searchRecordResult->push_back(pRecord2);
}

/**
*   Fills JNI details.
*/
void LoadJniPosRec(JNIEnv * env) {
    if (jniPosRec != NULL) return;
    jniPosRec = new JNI_POSREC;

    jniPosRec->cls = env->FindClass("com/test/StudentRecord");

    if(jniPosRec->cls != NULL){
        printf("sucessfully created class");
    }

    jniPosRec->constructortorID = env->GetMethodID(jniPosRec->cls, "<init>", "()V");
    if(jniPosRec->constructortorID != NULL){
        printf("sucessfully created ctorID");
    }

    jniPosRec->nameID = env->GetFieldID(jniPosRec->cls, "name", "Ljava/lang/String;");
    jniPosRec->rollNumberID = env->GetFieldID(jniPosRec->cls, "rollNumber", "I");
    jniPosRec->scoresID = env->GetFieldID(jniPosRec->cls, "scores", "[I");
    jniPosRec->departementID = env->GetFieldID(jniPosRec->cls, "departement", "Ljava/lang/String;");
    jniPosRec->totalMarkID = env->GetFieldID(jniPosRec->cls, "totalMark", "F");
    jniPosRec->hasReservationID = env->GetFieldID(jniPosRec->cls, "hasReservation", "Z");

}

void FillStudentRecValuesToJni(JNIEnv * env, jobject jPosRec, SearchRecord* cPosRec) {

    env->SetObjectField(jPosRec, jniPosRec->nameID, env->NewStringUTF(cPosRec->name.c_str()));
    jint rollNum = (jint)cPosRec->rollNumber;
    env->SetIntField(jPosRec, jniPosRec->rollNumberID, rollNum);
    // set scores array
    int len = sizeof(cPosRec->scores)/sizeof(int);
    jintArray j_arr = env->NewIntArray(len);
    env->SetIntArrayRegion(j_arr, 0, len, (jint*)cPosRec->scores);
    env->SetObjectField(jPosRec, jniPosRec->scoresID, j_arr);
    env->DeleteLocalRef(j_arr);

    env->SetObjectField(jPosRec, jniPosRec->departementID, env->NewStringUTF(cPosRec->departement.c_str()));
    jfloat totalMark = (jfloat)cPosRec->totalMark;
    env->SetFloatField( jPosRec, jniPosRec->totalMarkID, totalMark);
    jboolean hasReservation = cPosRec->hasReservation;
    env->SetBooleanField( jPosRec, jniPosRec->hasReservationID, hasReservation);
}

/**
* JNI method calling from JAVA
*/
JNIEXPORT void JNICALL Java_com_test_Test_getStudentDetails( JNIEnv *env, jclass cls, jobjectArray jPosRecArray)
{
    if (jPosRecArray == NULL) {
        printf("jPosRecArray is NULL\n");
        return;
    }
    jniPosRec = NULL;
    LoadJniPosRec(env);
    std::vector<SearchRecord*> searchRecordResult ;
    FillStudentRecordDetails(&searchRecordResult);
    printf("\nsearchRecordResult size is :%lu\n\n", searchRecordResult.size());

    for (size_t i = 0; i < searchRecordResult.size(); i++) {
        jobject jPosRec = env->NewObject(jniPosRec->cls, jniPosRec->constructortorID);
        FillStudentRecValuesToJni(env, jPosRec, searchRecordResult[i]);
        env->SetObjectArrayElement(jPosRecArray, i, jPosRec);
    }
    env->DeleteLocalRef(jPosRecArray);
    //return jPosRecArray;
}
