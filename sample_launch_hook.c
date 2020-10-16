/*
 * Copyright (C) 2020 Jolla Ltd.
 * Copyright (C) 2020 Open Mobile Platform LLC.
 * Copyright (C) 2020 Slava Monich <slava.monich@jolla.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *   3. Neither the names of the copyright holders nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * any official policies, either expressed or implied.
 */

#include "sample_plugin.h"

#include "jail_launch_hook_impl.h"
#include "jail_rules.h"

typedef JailLaunchHookClass SampleLaunchHookClass;
typedef struct sample_launch_hook {
    JailLaunchHook parent;
} SampleLaunchHook;

G_DEFINE_TYPE(SampleLaunchHook, sample_launch_hook, JAIL_TYPE_LAUNCH_HOOK)
#define TYPE (sample_launch_hook_get_type())
#define THIS(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE, SampleLaunchHook))

static
JailRules*
sample_launch_hook_confirm_launch(
    JailLaunchHook* hook,
    const JailApp* app,
    const JailCmdLine* cmd,
    const JailRunUser* user,
    JailRules* rules)
{
    GDEBUG("Approving launch");
    return jail_rules_ref(rules);
}

static
void
sample_launch_hook_launch_confirmed(
    JailLaunchHook* hook,
    const JailApp* app,
    const JailCmdLine* cmd,
    const JailRunUser* user,
    const JailRules* rules)
{
    GDEBUG("Launch confirmed");
}

static
void
sample_launch_hook_launch_denied(
    JailLaunchHook* hook,
    const JailApp* app,
    const JailCmdLine* cmd,
    const JailRunUser* user)
{
    GDEBUG("Launch denied");
}

static
void
sample_launch_hook_init(
    SampleLaunchHook* self)
{
}

static
void
sample_launch_hook_class_init(
    SampleLaunchHookClass* klass)
{
    klass->confirm_launch = sample_launch_hook_confirm_launch;
    klass->launch_confirmed = sample_launch_hook_launch_confirmed;
    klass->launch_denied = sample_launch_hook_launch_denied;
}

JailLaunchHook*
sample_launch_hook_new(
    void)
{
    return g_object_new(TYPE, NULL);
}

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
