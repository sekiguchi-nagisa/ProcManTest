#include <stdio.h>
#include <ProcMan.h>
#include <string.h>
#include <stdlib.h>

void single_test()
{
	printf("run single_test\n");
	GroupConfig gconfig = {1, SYNC_INVOKE, DISABLE, 0};

	int groupId = createProcGroup(gconfig);
	char **cmds = (char **)malloc(sizeof(char *) * 1);
	cmds[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds[0], "/usr/bin/python", 256);
	addProcToGroup(groupId, 1, cmds);

	invokeAll(groupId);
	deleteProcGroup(groupId);
}

void pipe_test2()
{
	printf("run pipe_test2\n");
	GroupConfig gconfig = {2, SYNC_INVOKE, DISABLE, 0};

	int groupId = createProcGroup(gconfig);

	char **cmds_pstree = (char **)malloc(sizeof(char *) * 2);
	cmds_pstree[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[0], "/usr/bin/pstree", 256);
	cmds_pstree[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[1], "-p", 256);
	addProcToGroup(groupId, 2, cmds_pstree);

	char **cmds_grep = (char **)malloc(sizeof(char *) * 2);
	cmds_grep[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[0], "/usr/bin/grep", 256);
	cmds_grep[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[1], "firefox", 256);
	addProcToGroup(groupId, 2, cmds_grep);

	invokeAll(groupId);
	deleteProcGroup(groupId);
}

void pipe_test3()
{
	printf("run pipe_test3\n");
	GroupConfig gconfig = {3, SYNC_INVOKE, DISABLE, 0};

	int groupId = createProcGroup(gconfig);

	char **cmds_pstree = (char **)malloc(sizeof(char *) * 2);
	cmds_pstree[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[0], "/usr/bin/pstree", 256);
	cmds_pstree[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[1], "-p", 256);
	addProcToGroup(groupId, 2, cmds_pstree);

	char **cmds_grep = (char **)malloc(sizeof(char *) * 2);
	cmds_grep[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[0], "/usr/bin/grep", 256);
	cmds_grep[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[1], "firefox", 256);
	addProcToGroup(groupId, 2, cmds_grep);

	char **cmds_grep2 = (char **)malloc(sizeof(char *) * 2);
	cmds_grep2[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep2[0], "/usr/bin/grep", 256);
	cmds_grep2[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep2[1], "k", 256);
	addProcToGroup(groupId, 2, cmds_grep2);

	invokeAll(groupId);
	deleteProcGroup(groupId);
}

void inRedir_test()
{
	printf("run inRedir_test\n");
	GroupConfig gconfig = {1, SYNC_INVOKE, DISABLE, 0};

	int groupId = createProcGroup(gconfig);

	char **cmds_cat = (char **)malloc(sizeof(char *) * 1);
	cmds_cat[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_cat[0], "/usr/bin/cat", 256);
	int procIndex = addProcToGroup(groupId, 1, cmds_cat);

	RedirectConfig *rconfig = (RedirectConfig *)malloc(sizeof(RedirectConfig));
	rconfig->fileName = (char *)malloc(sizeof(char) * 256);
	strncpy(rconfig->fileName, "/home/skgchxngsxyz-work/proc.c", 256);
	setRedirect(groupId, procIndex, 0, rconfig);

	invokeAll(groupId);
	deleteProcGroup(groupId);
}

void outRedir_test()
{
	printf("run outRedir_test\n");
	GroupConfig gconfig = {1, SYNC_INVOKE, DISABLE, 0};

	int groupId = createProcGroup(gconfig);

	char **cmds_pstree = (char **)malloc(sizeof(char *) * 2);
	cmds_pstree[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[0], "/usr/bin/pstree", 256);
	cmds_pstree[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[1], "-p", 256);
	int procIndex = addProcToGroup(groupId, 2, cmds_pstree);

	RedirectConfig *rconfig = (RedirectConfig *)malloc(sizeof(RedirectConfig));
	rconfig->targetType = FILE_TARGET;
//	rconfig->append = ENABLE;
	rconfig->fileName = (char *)malloc(sizeof(char) * 256);
	strncpy(rconfig->fileName, "/home/skgchxngsxyz-work/outredir.txt", 256);
	setRedirect(groupId, procIndex, 1, rconfig);

	invokeAll(groupId);
	deleteProcGroup(groupId);
}

int main()
{
	initContext();
	single_test();
	pipe_test2();
	pipe_test3();
	inRedir_test();
	outRedir_test();
	return 0;

}

