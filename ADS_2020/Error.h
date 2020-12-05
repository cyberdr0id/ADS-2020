#pragma once
#define ERROR_MAXSIZE_MESSAGE 200	
#define ERROR_MAX_ENTRY 100		
#define ERROR_THROW(id) Error::GetError(id);				
#define ERROR_THROW_IN(id, line, col) Error::GetError(id, line, col);
#define ERROR_ENTRY(id, message) {id, message}
#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(id, "Неопределенная ошибка")

#define ERROR_ENTRY_NODEF10(id)		ERROR_ENTRY_NODEF(id+0),ERROR_ENTRY_NODEF(id+1),ERROR_ENTRY_NODEF(id+2),ERROR_ENTRY_NODEF(id+3), \
									ERROR_ENTRY_NODEF(id + 4), ERROR_ENTRY_NODEF(id + 5), ERROR_ENTRY_NODEF(id + 6), ERROR_ENTRY_NODEF(id + 7), \
									ERROR_ENTRY_NODEF(id + 8), ERROR_ENTRY_NODEF(id + 9)


namespace Error
{
	struct ERROR								
	{
		int id;									
		char message[ERROR_MAXSIZE_MESSAGE];	
		struct IN								
		{
			short line = -1;					
			short col = -1;						
		} position;
	};

	ERROR GetError(int id);						
	ERROR GetError(int id, int line, int col);	
}