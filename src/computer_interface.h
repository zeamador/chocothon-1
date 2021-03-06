/*
	computer_interface.h
	Tuesday, August 23, 1994 11:25:40 PM (ajr)
	Thursday, May 25, 1995 5:18:03 PM- rewriting.

	New paradigm:
	Groups each start with one of the following groups:
	 #UNFINISHED, #SUCCESS, #FAILURE

	First is shown the
	#LOGON XXXXX

	Then there are any number of groups with:
	#INFORMATION, #CHECKPOINT, #SOUND, #MOVIE, #TRACK

	And a final:
	#INTERLEVEL TELEPORT, #INTRALEVEL TELEPORT

	Each group ends with:
	#END

	Groupings:
	#logon XXXX- login message (XXXX is shape for login screen)
	#unfinished- unfinished message
	#success- success message
	#failure- failure message
	#information- information
	#briefing XX- briefing, then load XX
	#checkpoint XX- Checkpoint xx (associated with goal)
	#sound XXXX- play sound XXXX
	#movie XXXX- play movie XXXX (from Movie file)
	#track XXXX- play soundtrack XXXX (from Music file)
	#interlevel teleport XXX- go to level XXX
	#intralevel teleport XXX- go to polygon XXX
	#pict XXXX- diplay the pict resource XXXX

	Special embedded keys:
	$B- Bold on
	$b- bold off
	$I- Italic on
	$i- italic off
	$U- underline on
	$u- underline off
	$- anything else is passed through unchanged

	Preprocessed format:
	static:
		long total_length;
		short grouping_count;
		short font_changes_count;
		short total_text_length;
	dynamic:
		struct terminal_groupings groups[grouping_count];
		struct text_face_data[font_changes_count];
		char text;
*/

/* ------------ structures */
struct static_preprocessed_terminal_data {
	short total_length;
	short flags;
	short lines_per_page; /* Added for internationalization/sync problems */
	short grouping_count;
	short font_changes_count;
};

struct view_terminal_data {
	short top, left, bottom, right;
	short vertical_offset;
};

extern byte *map_terminal_data;
extern long map_terminal_data_length;

/* ------------ prototypes */
void initialize_terminal_manager(void);
void initialize_player_terminal_info(short player_index);
void enter_computer_interface(short player_index, short text_number, short completion_flag);
void _render_computer_interface(struct view_terminal_data *data);
void update_player_for_terminal_mode(short player_index);
void update_player_keys_for_terminal(short player_index, long action_flags);
long build_terminal_action_flags(char *keymap);
void dirty_terminal_view(short player_index);
void abort_terminal_mode(short player_index);

boolean player_in_terminal_mode(short player_index);

void *get_terminal_data_for_save_game(void);
long calculate_terminal_data_length(void);

/* This returns the text.. */
void *get_terminal_information_array(void);
long calculate_terminal_information_length(void);

#ifdef PREPROCESSING_CODE
struct static_preprocessed_terminal_data *preprocess_text(char *text, short length);
struct static_preprocessed_terminal_data *get_indexed_terminal_data(short id);
void encode_text(struct static_preprocessed_terminal_data *terminal_text);
void decode_text(struct static_preprocessed_terminal_data *terminal_text);
void find_all_picts_references_by_terminals(byte *compiled_text, short terminal_count,
	short *picts, short *picture_count);
void find_all_checkpoints_references_by_terminals(byte *compiled_text,
	short terminal_count, short *checkpoints, short *checkpoint_count);
boolean terminal_has_finished_text_type(short terminal_id, short finished_type);
#endif
