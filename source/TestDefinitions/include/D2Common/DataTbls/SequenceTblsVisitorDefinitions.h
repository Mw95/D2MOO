#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <DataTbls/SequenceTbls.h>


BEGIN_VISIT(D2AnimSeqTxt)
	//FIELD(wSequence)
	//FIELD(nMode)
	//FIELD(nFrame)
	//FIELD(nDir)
	//OBJECT(nEvent)
END_VISIT()

BEGIN_VISIT(D2AnimSeqRecordStrc)
	//POINTER(pAnimSeqTxtRecord)
	//FIELD(nSeqFramesCount)
	//FIELD(nFramesCount)
END_VISIT()

BEGIN_VISIT(D2PlayerWeaponSequencesStrc)
	//ARRAY(weaponRecords)
END_VISIT()
