#include <stdio.h>
#include <ProcMan.h>
#include <string.h>
#include <stdlib.h>

void single_test()
{
	printf("run single_test\n");
	GroupConfig gconfig = {1, SYNC_INVOKE};
	ProcConfig pconfig = {1};

	int groupId = createProcGroup(gconfig);
	char **cmds = (char **)malloc(sizeof(char *) * 1);
	cmds[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds[0], "/usr/bin/python", 256);
	addProcToGroup(groupId, pconfig, cmds);
	invokeAll(groupId);
}

void pipe_test2()
{
	printf("run pipe_test2\n");
	GroupConfig gconfig = {2, SYNC_INVOKE};
	ProcConfig pconfig[] = {{2}, {2}};

	int groupId = createProcGroup(gconfig);

	char **cmds_pstree = (char **)malloc(sizeof(char *) * pconfig[0].cmdNum);
	cmds_pstree[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[0], "/usr/bin/pstree", 256);
	cmds_pstree[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[1], "-p", 256);
	addProcToGroup(groupId, pconfig[0], cmds_pstree);

	char **cmds_grep = (char **)malloc(sizeof(char *) * pconfig[1].cmdNum);
	cmds_grep[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[0], "/usr/bin/grep", 256);
	cmds_grep[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[1], "firefox", 256);
	addProcToGroup(groupId, pconfig[1], cmds_grep);
	invokeAll(groupId);
}

void pipe_test3()
{
	printf("run pipe_test3\n");
	GroupConfig gconfig = {3, SYNC_INVOKE};
	ProcConfig pconfig[] = {{2}, {2}, {2}};

	int groupId = createProcGroup(gconfig);

	char **cmds_pstree = (char **)malloc(sizeof(char *) * pconfig[0].cmdNum);
	cmds_pstree[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[0], "/usr/bin/pstree", 256);
	cmds_pstree[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_pstree[1], "-p", 256);
	addProcToGroup(groupId, pconfig[0], cmds_pstree);

	char **cmds_grep = (char **)malloc(sizeof(char *) * pconfig[1].cmdNum);
	cmds_grep[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[0], "/usr/bin/grep", 256);
	cmds_grep[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep[1], "firefox", 256);
	addProcToGroup(groupId, pconfig[1], cmds_grep);

	char **cmds_grep2 = (char **)malloc(sizeof(char *) * pconfig[2].cmdNum);
	cmds_grep2[0] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep2[0], "/usr/bin/grep", 256);
	cmds_grep2[1] = (char *)malloc(sizeof(char) * 256);
	strncpy(cmds_grep2[1], "k", 256);
	addProcToGroup(groupId, pconfig[2], cmds_grep2);

	invokeAll(groupId);
}

int main()
{
	initContext();
	single_test();
	pipe_test2();
	pipe_test3();
	return 0;

}

