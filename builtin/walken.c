/*
 * "git walken"
 *
 * Part of the "My First Object Walk" tutorial.
 */

#include "builtin.h"
#include "parse-options.h"
#include "config.h"
#include "revision.h"

int cmd_walken(int argc, const char **argv, const char *prefix)
{
    struct rev_info rev;
    const char * const walken_usage[] = {
        N_("git walken"),
        NULL,
	};

	struct option options[] = {
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, walken_usage, 0);
    git_config(git_walken_config, NULL);
    repo_init_revisions(the_repository, &rev, prefix);
    final_rev_info_setup(&rev);

	trace_printf(_("cmd_walken incoming...\n"));
	return 0;
}

static int git_walken_config(const char *var, const char *value, void *cb)
{
	/*
	 * For now, we don't have any custom configuration, so fall back to
	 * the default config.
	 */
	return git_default_config(var, value, cb);
}

static void final_rev_info_setup(struct rev_info *rev)
{
	/*
	 * We want to mimic the appearance of `git log --oneline`, so let's
	 * force oneline format.
	 */
	get_commit_format("oneline", rev);

	/* Start our object walk at HEAD. */
	add_head_to_pending(rev);
}

static void walken_commit_walk(struct rev_info *rev)
{
	if (prepare_revision_walk(rev))
		die(_("revision walk setup failed"));
}
